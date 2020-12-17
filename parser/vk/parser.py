from time import sleep
from bs4 import BeautifulSoup as bs
from credents import *
import collections
import requests
import re
from dynpage import *


headers = {
	"Referer":"https://m.vk.com/login?role=fast&to=&s=1&m=1}",
	'User-Agent':'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:50.0) Gecko/20100101 Firefox/50.0'
}
payload   = { 'email': login, 'pass': password }
login_url = "https://m.vk.com/login"

var_global= ""




class Parser:
	def __init__(self, login_url, headers, payload):
		self.headers = headers
		self.payload = payload
		self.login_url = login_url

		self.video_url = "https://vk.com/video"
		self.session   = None
		self.block_headers = []
		self.block_header_count = 0;
		self.video_meta_data = [] # results


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
	#	a) block header index
	# 	b) min/max video amount
	# 	c) min/max spend time
	# 	
	#> output:
	# 	a) amount of views
	# 	b) amount of likes
	# 	c) upload date
	def get_block_videos(self, idx):
		if ((idx-1) < 0 or (idx-1) > self.block_header_count):
			print("""[!] Error: invalid block header index.
    Use `show_block_headers' method to see content table""")


		block_header = self.block_headers[idx]
		print("[*] Parse video block:", block_header[0], " => ", block_header[1]); # get text value of video block

		video_page = self.session.get(self.video_url)
		video_soup = bs(video_page.content,'lxml')

		# Specific video block
		video_block      = video_soup.find("div", id=block_header[1])
		video_block_url  = video_block.findAll("a", class_="video_item__thumb_link")
		video_block_info = video_block.findAll("div", class_="video_item_info")

		#> Get: url, views, upload date, etc
		for i in range(len(video_block_url)):
			video_url   = video_block_url[i]['href']
			video_views = video_block_info[i].find("span", class_="video_item_views").text.rstrip('\n')
			video_upload= video_block_info[i].find("span", class_="video_item_updated").text.rstrip('\n')
			video_title = video_block_info[i].find("a", class_="video_item_title").text.rstrip('\n')
			video_title = re.sub(r'\s+', '', video_title)

			self.video_meta_data.append([video_url, video_views, video_upload])
			print(video_title, "\n", video_url, "\t=>", video_views, "\t=>", video_upload, '\n')

		return 0;





"""



Как удобно есть спагетти
    
https://vk.com/video-23702661_456255370
https://vk.com/


/video-65358263_456239153

# https://vk.com/video-35689279_456239226
"""



def main():
	obj = Parser(login_url, headers, payload)
	obj.auth()
	obj.get_video_block_headers()
	obj.show_block_headers()
	obj.get_block_videos(2)

	return 0;









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













