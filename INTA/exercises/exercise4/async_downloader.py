import asyncio
import sys

import httpx
from duckduckgo_search import DDGS

# a global object that we will use for all asynchronous requests
client = httpx.AsyncClient()

async def download_image_in_result(result):
    url = result["image"]
    try:
        print(f"Starting download: {url}")

        # await a new asynchronous request
        # (this is the main place where concurrency happens)
        response = await client.get(url)

        print(f"Finished download: {url}")

    except httpx.RequestError:
        print(f"ERROR: failed to download {url}", file=sys.stderr)
        return

    if response.status_code == 200:
        result["image_data"] = response.content
    else:
        print(f"ERROR: got status {response.status_code}", file=sys.stderr)

async def download_images(search_results):
    async with asyncio.TaskGroup() as tg:
        for result in search_results:
            # all results can be processed independently of each other,
            # so all tasks can be scheduled asynchronously
            tg.create_task(download_image_in_result(result))

if __name__ == "__main__":
    keywords = "cat"

    # collect the results returned by the search engine in a list
    search_results = []
    with DDGS() as ddgs:
        for result in ddgs.images(keywords, max_results=100):
            search_results.append(result)

    # download all images asynchronously
    asyncio.run(download_images(search_results))

    # TODO: upravte svůj "cat_downloader.py" z prvního cvičení pro asynchronní zpracování
    # TODO: změřte, jak dlouho trvá zpracování celého skriptu a porovnejte se synchronním zpracováním
