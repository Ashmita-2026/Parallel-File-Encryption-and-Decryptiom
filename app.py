from flask import Flask, request, render_template_string
import subprocess

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    html = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>CryptoSplice – UI</title>
        <style>
            body {
                margin: 0;
                padding: 0;
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                background: linear-gradient(to right, #141e30, #243b55);
                color: #fff;
            }

            .container {
                max-width: 600px;
                margin: 80px auto;
                background-color: rgba(255, 255, 255, 0.08);
                padding: 40px;
                border-radius: 12px;
                box-shadow: 0 10px 25px rgba(0, 0, 0, 0.2);
            }

            h1 {
                text-align: center;
                margin-bottom: 10px;
                font-size: 36px;
                color: #ffda6c;
            }

            p {
                text-align: center;
                font-size: 14px;
                margin-bottom: 30px;
                color: #ddd;
            }

            label {
                display: block;
                margin-top: 20px;
                font-weight: bold;
            }

            input[type="text"], select {
                width: 100%;
                padding: 10px;
                margin-top: 5px;
                border: none;
                border-radius: 6px;
                background: #f5f5f5;
                color: #333;
            }

            button {
                margin-top: 30px;
                width: 100%;
                padding: 12px;
                background: #ffda6c;
                border: none;
                border-radius: 6px;
                font-weight: bold;
                color: #333;
                cursor: pointer;
                transition: background 0.3s;
            }

            button:hover {
                background: #ffe88a;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <h1>CryptoSplice</h1>
            <p>Secure your data with a splice of encryption.</p>
            <form method="POST">
                <label for="folder">Directory Path:</label>
                <input type="text" name="folder" id="folder" required>

                <label for="action">Action:</label>
                <select name="action" id="action" required>
                    <option value="encrypt">Encrypt</option>
                    <option value="decrypt">Decrypt</option>
                </select>

                <button type="submit">Run</button>
            </form>
        </div>
    </body>
    </html>
    """

    if request.method == 'POST':
        folder = request.form['folder']
        action = request.form['action'].lower()  # ✅ Ensures lowercase (encrypt/decrypt)
        try:
            result = subprocess.run(
                ['./encrypt_decrypt'],
                input=f"{folder}\n{action}\n",
                text=True,
                capture_output=True
            )

            return f"""
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <title>CryptoSplice – Result</title>
                <style>
                    body {{
                        margin: 0;
                        padding: 0;
                        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                        background: linear-gradient(to right, #1e3c72, #2a5298);
                        color: #fff;
                    }}

                    .container {{
                        max-width: 800px;
                        margin: 80px auto;
                        background-color: rgba(255, 255, 255, 0.1);
                        padding: 30px 40px;
                        border-radius: 12px;
                        box-shadow: 0 10px 25px rgba(0, 0, 0, 0.2);
                    }}

                    h1 {{
                        text-align: center;
                        color: #fff;
                        margin-bottom: 20px;
                    }}

                    pre {{
                        background-color: rgba(0, 0, 0, 0.5);
                        padding: 20px;
                        border-radius: 10px;
                        white-space: pre-wrap;
                        font-size: 15px;
                        line-height: 1.6;
                        color: #e8e8e8;
                    }}

                    a {{
                        display: block;
                        margin-top: 25px;
                        text-align: center;
                        color: #ffda6c;
                        text-decoration: none;
                        font-weight: bold;
                    }}

                    a:hover {{
                        color: #fff;
                        text-decoration: underline;
                    }}
                </style>
            </head>
            <body>
                <div class="container">
                    <h1>CryptoSplice Result</h1>
                    <pre>{result.stdout}</pre>
                    <a href="/">← Back to Home</a>
                </div>
            </body>
            </html>
            """
        except Exception as e:
            return f"<h2>Error:</h2><pre>{str(e)}</pre><a href='/'>← Back</a>"

    return render_template_string(html)

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
