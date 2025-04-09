# from bs4 import BeautifulSoup
# import requests
# import time
#
#
# def get_html(url):
#     response = requests.get(url)
#     return response.text
#
#
# with open('goyda.txt', 'w', encoding='utf-8') as f:
#     for i in range(1, 19):
#         url = f'https://faq8.ru/list.php?2,page={i}'
#         html = get_html(url)
#         soup = BeautifulSoup(html, 'html.parser')
#         for row in (soup.find_all('table')[1]).find_all('tr')[1:]:
#             tds = row.find_all('td')
#             try:
#                 theme, author = [j.text.strip() for j in tds[1].find_all('a')]
#             except ValueError:
#                 author = '-'
#             views, messages, timestamp = [j.text.strip() for j in tds[2:]]
#             f.write(';'.join([theme, author, views, messages, timestamp]) + '\n')
#         time.sleep(1)
#mx = [0 for i in range(7)]
#with open('forum.txt', 'r', encoding='utf-8') as f:
#    for i in f:
#        s = i.split(';')
#        try:
#            for j in range(7):
#                mx[j] = max(len(s[j]), mx[j])
#        except:
#            continue
#print(mx)
import time
from datetime import datetime

data_format = "%d.%m.%Y, %H:%M"

with open('forum.txt', 'w', encoding='utf-8') as f:
    with open('forum2.txt', 'r', encoding='utf-8') as g:
        f.write(g.readline()) 
        for i in g:
            s = i.split(';')
            try:
                s[2] = s[2].replace(',', '')
            except:
                print(s)
            f.write(';'.join(s))
