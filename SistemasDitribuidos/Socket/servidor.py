import http.server
import socketserver
import os

PORT = 8088
DIRECTORY = "C:/Users/bruno/Documents/GitHub/CollegeCodes/SistemasDitribuidos/Socket"

class SimpleHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=DIRECTORY, **kwargs)

    def do_GET(self):
        try:
            if os.path.exists(DIRECTORY + self.path):
                super().do_GET()
            else:
                self.send_response(404)
                self.end_headers()
                self.wfile.write(b"Erro 404: Arquivo nao encontrado.")
        except Exception as e:
            self.send_response(500)
            self.end_headers()
            self.wfile.write(b"Erro 500: Erro interno do servidor.")

handler = SimpleHTTPRequestHandler
with socketserver.TCPServer(("", PORT), handler) as httpd:
    print(f"Servindo na porta {PORT}...")   
    httpd.serve_forever()
