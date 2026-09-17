from flask import Flask, request, jsonify
import sqlite3
import datetime

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('voltwatch.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS readings
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  timestamp TEXT,
                  average INTEGER,
                  peak_to_peak INTEGER,
                  surge INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.json
    conn = sqlite3.connect('voltwatch.db')
    c = conn.cursor()
    c.execute("INSERT INTO readings (timestamp, average, peak_to_peak, surge) VALUES (?, ?, ?, ?)",
              (datetime.datetime.now().isoformat(),
               data['average'],
               data['peak_to_peak'],
               data.get('surge',0)))
    conn.commit()
    conn.close()
    print(f"Received - Average: {data['average']} | Peak to Peak: {data['peak_to_peak']}")
    return jsonify({"status": "ok"})

if __name__ == '__main__':
    init_db()
    app.run(host='0.0.0.0', port=5000, debug=True)