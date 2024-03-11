from pathlib import Path
from pprint import pprint
import sys
import traceback
import typing
from urllib.parse import urlparse

import requests
from duckduckgo_search import DDGS

def search(keywords: str, **kwargs) -> typing.Iterator[dict]:
    """ Search images using DuckDuckGo search engine.

    Args:
        keywords: the search terms (e.g. "cat")
        kwargs: additional arguments of the search library, see
                https://github.com/deedy5/duckduckgo_search?tab=readme-ov-file#3-images---image-search-by-duckduckgocom
    Yields:
        dict with the search results
    """
    with DDGS() as ddgs:
        for result in ddgs.images(keywords, **kwargs):
            url = result["image"]
            print(f"Downloading {url}")
            try:
                response = requests.get(url)
            except requests.RequestException:
                print(f"ERROR: failed to download {url}", file=sys.stderr)
                continue
            if response.status_code == 200:
                result["image_data"] = response.content
                yield result
            else:
                print(f"ERROR: got status {response.status_code}", file=sys.stderr)

def save(result: dict, directory: Path) -> None:
    """ Save image of the search result to a file in a directory.

    Args:
        result: dict with the search result data
        directory: where to save the file
    """
    # ensure that the directory exists
    directory.mkdir(parents=True, exist_ok=True)

    # extract the file name
    name = Path(urlparse(result["image"]).path)
    if name.suffix.lower() not in [".jpg", ".jpeg", ".png", ".gif", ".webp"]:
        print(f"Skipping result because an image suffix was not found in URL {result['image']}")
        return
    name = name.name

    try:
        with open(directory / name, "wb") as file:
            file.write(result["image_data"])
    except OSError as e:
        #traceback.print_exception(e, file=sys.stderr)
        print(f"OSError: {e}", file=sys.stderr)

# TODO: modify imgs_dir to separate different keywords, type_image, etc. into subdirectories
keywords = "cat"
imgs_dir = Path("images")
for result in search(keywords, max_results=100):
    save(result, imgs_dir)

