#include <iostream>
#include <fstream>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Helper: Read file into string
string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// Helper: Write string to file
void writeFile(const string& filename, const string& data) {
    ofstream file(filename, ios::binary);
    file.write(data.c_str(), data.size());
}

// AES Encryption (ECB/CFB)
void aesEncrypt(const string& inputFile, const string& outputFile, const string& keyHex, const string& mode, int keyBits) {
    string plaintext = readFile(inputFile);
    string ciphertext(plaintext.size() + AES_BLOCK_SIZE, 0);

    AES_KEY encKey;
    unsigned char key[32] = {0}; // 256-bit max
    string keyBin = keyHex.substr(0, keyBits / 4);
    for (size_t i = 0; i < keyBin.length() / 2; ++i) {
        sscanf(keyBin.substr(i * 2, 2).c_str(), "%02hhx", &key[i]);
    }

    if (mode == "ECB") {
        AES_set_encrypt_key(key, keyBits, &encKey);
        for (size_t i = 0; i < plaintext.size(); i += AES_BLOCK_SIZE) {
            AES_ecb_encrypt((unsigned char*)&plaintext[i], (unsigned char*)&ciphertext[i], &encKey, AES_ENCRYPT);
        }
    } else if (mode == "CFB") {
        AES_set_encrypt_key(key, keyBits, &encKey);
        unsigned char iv[AES_BLOCK_SIZE] = {0};
        int num = 0;
        AES_cfb128_encrypt((unsigned char*)plaintext.data(), (unsigned char*)ciphertext.data(), plaintext.size(), &encKey, iv, &num, AES_ENCRYPT);
    }

    writeFile(outputFile, ciphertext);
    cout << "Encrypted and saved to " << outputFile << endl;
}

// AES Decryption
void aesDecrypt(const string& inputFile, const string& keyHex, const string& mode, int keyBits) {
    string ciphertext = readFile(inputFile);
    string plaintext(ciphertext.size(), 0);

    AES_KEY decKey;
    unsigned char key[32] = {0};
    string keyBin = keyHex.substr(0, keyBits / 4);
    for (size_t i = 0; i < keyBin.length() / 2; ++i) {
        sscanf(keyBin.substr(i * 2, 2).c_str(), "%02hhx", &key[i]);
    }

    if (mode == "ECB") {
        AES_set_decrypt_key(key, keyBits, &decKey);
        for (size_t i = 0; i < ciphertext.size(); i += AES_BLOCK_SIZE) {
            AES_ecb_encrypt((unsigned char*)&ciphertext[i], (unsigned char*)&plaintext[i], &decKey, AES_DECRYPT);
        }
    } else if (mode == "CFB") {
        AES_set_encrypt_key(key, keyBits, &decKey);
        unsigned char iv[AES_BLOCK_SIZE] = {0};
        int num = 0;
        AES_cfb128_encrypt((unsigned char*)ciphertext.data(), (unsigned char*)plaintext.data(), ciphertext.size(), &decKey, iv, &num, AES_DECRYPT);
    }

    cout << "Decrypted text:\n" << plaintext << endl;
}

// RSA Key Generation
void generateRSAKeys() {
    RSA *rsa = RSA_new();
    BIGNUM *e = BN_new();
    BN_set_word(e, RSA_F4);

    RSA_generate_key_ex(rsa, 2048, e, nullptr);
    BIO *pri = BIO_new_file("rsa_priv.pem", "w+");
    BIO *pub = BIO_new_file("rsa_pub.pem", "w+");

    PEM_write_bio_RSAPrivateKey(pri, rsa, nullptr, nullptr, 0, nullptr, nullptr);
    PEM_write_bio_RSAPublicKey(pub, rsa);

    BIO_free_all(pri);
    BIO_free_all(pub);
    RSA_free(rsa);
    BN_free(e);
    cout << "RSA keys generated.\n";
}

// RSA Encryption/Decryption
void rsaEncryptDecrypt(const string& text) {
    generateRSAKeys();

    RSA *pub = RSA_new();
    BIO *pubkey = BIO_new_file("rsa_pub.pem", "r");
    PEM_read_bio_RSAPublicKey(pubkey, &pub, nullptr, nullptr);

    unsigned char encrypted[256];
    int len = RSA_public_encrypt(text.size(), (unsigned char*)text.c_str(), encrypted, pub, RSA_PKCS1_OAEP_PADDING);

    RSA *priv = RSA_new();
    BIO *privkey = BIO_new_file("rsa_priv.pem", "r");
    PEM_read_bio_RSAPrivateKey(privkey, &priv, nullptr, nullptr);

    unsigned char decrypted[256];
    int dlen = RSA_private_decrypt(len, encrypted, decrypted, priv, RSA_PKCS1_OAEP_PADDING);

    cout << "Decrypted Text: " << string((char*)decrypted, dlen) << endl;

    BIO_free_all(pubkey);
    BIO_free_all(privkey);
    RSA_free(pub);
    RSA_free(priv);
}

// SHA-256 Hash
void sha256Hash(const string& filename) {
    string data = readFile(filename);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)data.c_str(), data.length(), hash);

    cout << "SHA-256: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", hash[i]);
    cout << endl;
}

// RSA Signature and Verification
void rsaSignVerify(const string& file) {
    string data = readFile(file);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)data.c_str(), data.length(), hash);

    RSA *priv = RSA_new();
    BIO *privkey = BIO_new_file("rsa_priv.pem", "r");
    PEM_read_bio_RSAPrivateKey(privkey, &priv, nullptr, nullptr);

    unsigned char* sig = new unsigned char[RSA_size(priv)];
    unsigned int sigLen;
    RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, sig, &sigLen, priv);
    writeFile("sig.bin", string((char*)sig, sigLen));

    BIO_free_all(privkey);
    RSA_free(priv);

    RSA *pub = RSA_new();
    BIO *pubkey = BIO_new_file("rsa_pub.pem", "r");
    PEM_read_bio_RSAPublicKey(pubkey, &pub, nullptr, nullptr);
    string sigFile = readFile("sig.bin");

    bool verified = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, (unsigned char*)sigFile.c_str(), sigFile.size(), pub);
    cout << "Signature Verification: " << (verified ? "Success" : "Failed") << endl;

    RSA_free(pub);
    BIO_free_all(pubkey);
    delete[] sig;
}

// Timer Wrapper
template<typename Func>
void timedOperation(const string& label, Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << label << " took " << duration.count() << " ms\n";
}

// Main Menu
int main() {
    int choice;
    string file, mode, key, text;
    int keyBits;

    while (true) {
        cout << "\nChoose Operation:\n"
             << "1. AES Encrypt\n2. AES Decrypt\n3. RSA Encrypt/Decrypt\n4. RSA Signature\n5. SHA-256 Hash\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Input file: "; cin >> file;
                cout << "Key (hex): "; cin >> key;
                cout << "Key size (128/256): "; cin >> keyBits;
                cout << "Mode (ECB/CFB): "; cin >> mode;
                timedOperation("AES Encryption", [&]() { aesEncrypt(file, "aes_out.bin", key, mode, keyBits); });
                break;
            case 2:
                cout << "Encrypted file: "; cin >> file;
                cout << "Key (hex): "; cin >> key;
                cout << "Key size (128/256): "; cin >> keyBits;
                cout << "Mode (ECB/CFB): "; cin >> mode;
                timedOperation("AES Decryption", [&]() { aesDecrypt(file, key, mode, keyBits); });
                break;
            case 3:
                cout << "Enter text to encrypt: "; cin.ignore(); getline(cin, text);
                timedOperation("RSA Encrypt/Decrypt", [&]() { rsaEncryptDecrypt(text); });
                break;
            case 4:
                cout << "File to sign: "; cin >> file;
                timedOperation("RSA Signature", [&]() { rsaSignVerify(file); });
                break;
            case 5:
                cout << "File to hash: "; cin >> file;
                timedOperation("SHA-256 Hash", [&]() { sha256Hash(file); });
                break;
            case 0:
                return 0;
        }
    }
}
