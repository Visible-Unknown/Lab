# Lab 4: Programming Symmetric & Asymmetric Cryptography

## Course: CSE-462 Introduction to Computer Security Lab

**Name:** Al Amin Hossain

---

## 🔍 Objectives

* To implement symmetric and asymmetric cryptographic algorithms using C++.
* To explore key-based encryption/decryption operations and digital signatures.
* To understand cryptographic hashing using SHA-256.
* To measure and compare the execution time for cryptographic operations.

---

## 🛠️ Features Implemented in the Program

A single C++ program was developed using OpenSSL to perform the following tasks:

### ✅ Symmetric Cryptography - AES

* AES Encryption/Decryption using 128-bit and 256-bit keys.
* Supports **ECB** and **CFB** modes.
* Accepts plaintext files and produces encrypted output files.
* Supports decryption from encrypted file.

### ✅ Asymmetric Cryptography - RSA

* RSA key generation (2048-bit).
* RSA Encryption and Decryption of text.

### ✅ RSA Digital Signature

* SHA-256 hash is computed for a file.
* Signature is generated using the private RSA key.
* Signature verification is done using the public key.

### ✅ Hashing - SHA-256

* Computes the SHA-256 digest of any input file and prints it on the console.

### ✅ Timing Analysis

* Measures execution time of each operation using C++ `chrono` library.
* Helps visualize performance impact of different key lengths.

---

## 📂 File Structure

| File              | Description                                 |
| ----------------- | ------------------------------------------- |
| `lab4_crypto.cpp` | Main C++ source code implementing all tasks |
| `rsa_priv.pem`    | Generated RSA Private Key (PEM format)      |
| `rsa_pub.pem`     | Generated RSA Public Key (PEM format)       |
| `aes_out.bin`     | Output file for AES encrypted data          |
| `sig.bin`         | RSA signature file                          |

---

## 📦 Dependencies

* **OpenSSL library** (`libssl-dev`, `libcrypto++` if available)
* C++ compiler (`g++` recommended)

Install dependencies on Ubuntu:

```bash
sudo apt-get install libssl-dev
```

---

## ⚙️ How to Compile and Run

### 🔧 Compile

```bash
g++ lab4_crypto.cpp -o lab4_crypto -lcrypto -lssl
```

### ▶️ Run

```bash
./lab4_crypto
```

Follow the on-screen menu to select an operation:

* AES Encrypt
* AES Decrypt
* RSA Encrypt/Decrypt
* RSA Signature
* SHA-256 Hash

---

## ⏱️ Sample Execution Time Observations

| Operation     | Key Size | Mode | Time (ms) |
| ------------- | -------- | ---- | --------- |
| AES Encrypt   | 128-bit  | ECB  | \~1.2 ms  |
| AES Encrypt   | 256-bit  | CFB  | \~1.6 ms  |
| RSA Encrypt   | 2048-bit | -    | \~10 ms   |
| RSA Signature | 2048-bit | -    | \~9 ms    |
| SHA-256 Hash  | -        | -    | \~0.3 ms  |

> Times vary depending on input size and machine specs.

---

## 🌐 References

* OpenSSL C++ usage: [https://wiki.openssl.org/index.php/EVP\_Symmetric\_Encryption\_and\_Decryption](https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption)
* RSA Signature: [https://www.openssl.org/docs/man1.1.1/man3/RSA\_sign.html](https://www.openssl.org/docs/man1.1.1/man3/RSA_sign.html)
* AES in ECB/CFB modes: [https://www.openssl.org/docs/man1.1.1/man3/AES\_encrypt.html](https://www.openssl.org/docs/man1.1.1/man3/AES_encrypt.html)

---

## ✅ Submission Checklist

* [x] Source Code (`lab4_crypto.cpp`)
* [x] Encrypted/Decrypted Sample Files
* [x] Signature and Hash Output Files
* [x] README Report (this file)

---

## 📌 Conclusion

This lab provided a deep dive into the programming side of cryptography. Writing AES and RSA routines using OpenSSL C++ APIs gave clarity into the internal mechanisms of encryption, hashing, and digital signatures. The addition of execution time tracking offered real-world performance insights.

---

> Lab completed and tested successfully. All required functionalities implemented as per instruction.
