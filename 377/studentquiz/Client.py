import socket

HOST = '0.tcp.ngrok.io'  # The server's hostname or IP address
PORT = 17607       # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    def getMessage(task=None):
        data = b''
        while True:
            buffer = s.recv(1024)
            if len(buffer) == 0:
                break
            else:
                data += buffer
                if(len(buffer) != 1024):
                    break
        msg = ""
        try:
            msg = data.decode()
        except Exception as e:
            if task != None:
                print("Error decoding input during", task)
            else:
                print("Error decoding input")
            print(e)
        return msg
    while True:
        data = getMessage()
        print(data)
        s.sendall(input().encode())