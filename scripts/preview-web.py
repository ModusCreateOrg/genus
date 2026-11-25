"""Serve the Genus browser build on localhost."""

import argparse
from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.request import urlopen
import webbrowser


def preview(directory):
    url = "http://127.0.0.1:8000/"
    handler = partial(SimpleHTTPRequestHandler, directory=str(directory))
    try:
        server = ThreadingHTTPServer(("127.0.0.1", 8000), handler)
    except OSError:
        try:
            with urlopen(url, timeout=2) as response:
                already_serving = response.read() == (directory / "index.html").read_bytes()
        except OSError:
            already_serving = False
        if not already_serving:
            raise SystemExit(f"Could not start the preview. Another service may be using {url}")
        print(f"Preview already running at {url}", flush=True)
        webbrowser.open(url)
        return

    with server:
        print(f"Serving Genus at {url}", flush=True)
        webbrowser.open(url)
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            pass


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory", type=Path, help="Directory containing index.html.")
    args = parser.parse_args()
    preview(args.directory)


if __name__ == "__main__":
    main()

