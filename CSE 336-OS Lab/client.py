# Reg no.: 2020331057
# Name   : Al-Amin

import socket
import threading
import tkinter as tk
from tkinter import scrolledtext
from tkinter import messagebox

# HOST = '10.100.165.152'
HOST = '10.101.3.176-'
PORT = 1234

LIGHT_YELLOW = '#FFFF99'
DARK_GREEN = '#006400'
LIGHT_GREEN = '#32CD32'
BLACK = "black"
FONT = ("Arial", 15)
BUTTON_FONT = ("Arial", 13)
SMALL_FONT = ("Arial", 11)

# Creating a socket object
# AF_INET: we are going to use IPv4 addresses
# SOCK_STREAM: we are using TCP packets for communication
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def add_message(message):
    message_box.config(state=tk.NORMAL)
    message_box.insert(tk.END, message + '\n')
    message_box.config(state=tk.DISABLED)

def connect():

    try:

        # Connect to the server
        client.connect((HOST, PORT))
        print("Successfully connected to server")
        add_message("[SERVER] Successfully connected to the server")
    except:
        messagebox.showerror("Unable to connect to server", f"Unable to connect to server {HOST} {PORT}")

    username = username_textbox.get()
    if username != '':
        client.sendall(username.encode())
    else:
        messagebox.showerror("Invalid username", "Username cannot be empty!")

    threading.Thread(target=listen_for_messages_from_server, args=(client, )).start()

    username_textbox.config(state=tk.DISABLED)
    username_button.config(state=tk.DISABLED)

def send_message():
    message = message_textbox.get()
    if message != '':
        client.sendall(message.encode())
        message_textbox.delete(0, len(message))
    else:
        messagebox.showerror("Empty message", "Message cannot be empty!")



root = tk.Tk()
root.geometry("600x600")
root.title("Chat Box")
root.resizable(False, False)
root.config(bg=LIGHT_YELLOW)

root.grid_rowconfigure(0, weight=1)
root.grid_rowconfigure(1, weight=4)
root.grid_rowconfigure(2, weight=1)

top_frame = tk.Frame(root, width=600, height=100, bg=DARK_GREEN)
top_frame.grid(row=0, column=0, sticky=tk.NSEW)

middle_frame = tk.Frame(root, width=600, height=400, bg=LIGHT_GREEN)
middle_frame.grid(row=1, column=0, sticky=tk.NSEW)

bottom_frame = tk.Frame(root, width=600, height=100, bg=DARK_GREEN)
bottom_frame.grid(row=2, column=0, sticky=tk.NSEW)

username_label = tk.Label(top_frame, text="Enter username:", font=FONT, bg=DARK_GREEN, fg=BLACK)
username_label.pack(side=tk.LEFT, padx=10)

username_textbox = tk.Entry(top_frame, font=FONT, bg=LIGHT_GREEN, fg=BLACK, width=23)
username_textbox.pack(side=tk.LEFT)

username_button = tk.Button(top_frame, text="Join", font=BUTTON_FONT, bg=LIGHT_YELLOW, fg=BLACK, command=connect)
username_button.pack(side=tk.LEFT, padx=15)

message_textbox = tk.Entry(bottom_frame, font=FONT, bg=LIGHT_GREEN, fg=BLACK, width=38)
message_textbox.pack(side=tk.LEFT, padx=10)

message_button = tk.Button(bottom_frame, text="Send", font=BUTTON_FONT, bg=LIGHT_YELLOW, fg=BLACK, command=send_message)
message_button.pack(side=tk.LEFT, padx=10)

message_box = scrolledtext.ScrolledText(middle_frame, font=SMALL_FONT, bg=LIGHT_GREEN, fg=BLACK, width=67, height=26.5)
message_box.config(state=tk.DISABLED)
message_box.pack(side=tk.TOP)


def listen_for_messages_from_server(client):

    while 1:

        message = client.recv(2048).decode('utf-8')
        if message != '':
            username = message.split("~")[0]
            content = message.split('~')[1]

            add_message(f"[{username}] {content}")
            
        else:
            messagebox.showerror("Error", "Message recevied from client is empty")

# main function
def main():

    root.mainloop()
    
if __name__ == '__main__':
    main()