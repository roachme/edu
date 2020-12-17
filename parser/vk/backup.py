from time import sleep
from bs4 import BeautifulSoup as bs
import vk_api
from credents import *
import collections
import requests


headers = {
    "Referer":"https://m.vk.com/login?role=fast&to=&s=1&m=1}",
    'User-Agent':'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:50.0) Gecko/20100101 Firefox/50.0'
}
payload   = { 'email': login, 'pass': password }
login_url = "https://m.vk.com/login"


class Parser:
    def __init__(self, login_url, headers, payload):
        self.headers = headers
        self.payload = payload
        self.login_url = login_url

        self.video_url = "https://vk.com/video"
        self.session   = None
        self.block_headers = []
        self.block_header_count = 0;


    def  fake_func(self, idx):
        video_block = self.block_headers[idx]
        print("[*] Parse video block:", video_block[0]); # get text value of video block

        print("https://vk.com/video-42871045_456239502")
        sleep(0.5)
        print("https://vk.com/video-35689279_456239226")
        sleep(0.5)
        print("https://vk.com/video-174310051_456239986")
        sleep(0.5)
        print("https://vk.com/video-174310051_456240014")
        sleep(0.5)
        print("https://vk.com/video-9159189_456245575")
        sleep(0.5)
        print("https://vk.com/video-165026090_456240490")
        sleep(0.5)
        print("https://vk.com/video-9693056_456241877")



    def auth(self):
        self.session = requests.Session()
        login_page   = self.session.get(self.login_url)
        login_soup   = bs(login_page.content, 'lxml')
        login_url    = login_soup.find('form')['action']
        login_page   = self.session.post(self.login_url, 
                       data=self.payload, headers=self.headers)

        if (login_page.status_code == 200):
            print("[*] Loged in")
        else:
            print("[!] Failed to log in: ", login_page.status_code)
        return login_page.status_code


    def vk_func(self):
        print("vk_func")


    # You can see header tag value as well. `header[1]' is that
    def show_block_headers(self):
        i = 1;
        print()
        print("[*] Block headers: ", self.block_header_count)
        for header in self.block_headers:
            #print("{i}\t{text}".format(i=i, text=header[0]))
            print("{i}\t{tag}\t\t => {text}<br/>".format(i=i, tag=header[1], text=header[0]))
            i += 1
        
        return print()


    # Block headers: 16 + 1(my videos)
    def get_video_block_headers(self):
        block_headers = []
        count = 0

        print("[*] Parse video page")
        video_page = self.session.get(self.video_url)
        video_soup = bs(video_page.content,'lxml')
        video_block_headers  = video_soup.findAll("div", class_='page_block videocat_page_block') # page_block_header_inner _header_inner


        for header in video_block_headers:
            header_tag  = header['id']
            header_text = header.find("div", class_="page_block_header_inner _header_inner")
            header_text = header_text.text.rstrip('\n') # strip newlines if exist

            # [0] Header text name; [1] Header tag name
            header = [header_text, header_tag]
            block_headers.append(header)
            count += 1;

        self.block_headers = block_headers;
        self.block_header_count = count;
        return 0;






    # Get videos from specific block
    # You can specify in/out arguments as well
    #> input:
    #   a) block header index
    #   b) min/max video amount
    #   c) min/max spend time
    #   
    #> output:
    #   a) amount of views
    #   b) amount of likes
    #   c) upload date
    def get_block_videos(self, idx):
        idx -= 1
        if (idx < 0 or idx > self.block_header_count):
            print("""[!] Error: invalid block header index.
    Use `show_block_headers' method to see content table""")

        block_header = self.block_headers[idx]
        print("[*] Parse video block:", block_header[0], " => ", block_header[1]); # get text value of video block

        video_page = self.session.get(self.video_url)
        video_soup = bs(video_page.content,'lxml')

        # get entire html for specific block
        # tag: videocat_page_block_trends
        video_block = video_soup.find("div", id=block_header[1])
        print(video_block)
        video_block = video_block.findAll("a", class_="video_item__thumb_link")
        for video in video_block:
            #print(video['href'])
            pass



        return 0;



"""
Как удобно есть спагетти
    
https://vk.com/video-51189706_456246877

# https://vk.com/video-35689279_456239226
"""





def main():
    obj = Parser(login_url, headers, payload)
    obj.auth()
    obj.get_video_block_headers()
    obj.show_block_headers()
    obj.get_block_videos(1)

    return 0;



main()




""" Video block
    <div class="videocat_other_blocks">

    <div class="page_block videocat_page_block" id=
    "videocat_page_block_lives" data-type="lives">

    <div class="page_block videocat_page_block" id=
    "videocat_page_block_trends" data-type="trends">

    <div class="page_block videocat_page_block" id=
    "videocat_page_block_games" data-type="games">


"""

"""
<div class="page_block_header_inner _header_inner">
    <a class="ui_crumb" href="/videos0" onclick="return nav.go(this, event, {back: true});">Мои видео</a>
    <div class="ui_crumb_sep"></div><div class="ui_crumb">Добавление видео</div>

</div>


"""













