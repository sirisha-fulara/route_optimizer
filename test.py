from flask import Flask, jsonify, request, render_template
from flask_cors import CORS
import sys
import os
import ctypes
python_dll = os.path.join(sys.exec_prefix, 'python313.dll')

# Load it remove in git 
try:
    ctypes.WinDLL(python_dll) 
    print("✅ Python DLL loaded successfully from:", python_dll)
except OSError as e:
    print("❌ Failed to load Python DLL:", e)
# Add the root folder to sys.path dynamically (3 levels up from this file)
#linus code for render 
# import importlib.util
# # Set correct relative path to .so file
# cpp_backend_dir = os.path.abspath("cpp_backend")
# so_path = os.path.join(cpp_backend_dir, "route_optimizer.cpython-312-x86_64-linux-gnu.so")

# # Add cpp_backend to sys.path if needed
# if cpp_backend_dir not in sys.path:
#     sys.path.insert(0, cpp_backend_dir)

# # Dynamically load the shared object (.so)
# spec = importlib.util.spec_from_file_location("route_optimizer", so_path)
# route_optimizer = importlib.util.module_from_spec(spec)
# spec.loader.exec_module(route_optimizer)

print("✅ C++ backend (.so) module loaded successfully.") 

# Setup for compiled C++ module
module_path = os.path.abspath("cpp_backend/build/release")
if module_path not in sys.path:
    sys.path.insert(0, module_path)

import route_optimizer

app = Flask(__name__)
CORS(app)

@app.route("/")
def index():
    return render_template("index.html")  # <- Serves the frontend

@app.route("/run_dijkstra", methods=['POST'])
def run_dijkstra():
    data = request.get_json()
    cities = data['cities']
    city_index = {city: i for i, city in enumerate(cities)}
    num_nodes = len(cities)
    
    g = route_optimizer.Graph(num_nodes)
    for edge in data['edges']:
        u = city_index[edge['u']]
        v = city_index[edge['v']]
        g.addEdge(u, v, edge['w'])

    src = city_index[data['src']]
    dest = city_index[data['dest']]
    dist, parent = route_optimizer.Dijkstra(g, src, num_nodes)

    return jsonify({
        'distances': dist,
        'parent': parent,
        'path': [cities[i] for i in reconstruct_path(parent, src, dest)]
    })

def reconstruct_path(parent, src, dest):
    path = []
    while dest != -1:
        path.append(dest)
        dest = parent[dest]
    return path[::-1] if path and path[-1] == src else []

if __name__ == '__main__':
    app.run(debug=True)
