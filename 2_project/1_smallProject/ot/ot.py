# %%
import requests
from bs4 import BeautifulSoup
import json

# %%

url = "https://passport.eteams.cn/papi/passport/login/pclogin"
# url = "https://passport.eteams.cn"

headers = {
    "authority": "passport.eteams.cn",
    "method": "POST",
    "path": "/papi/passport/login/pclogin",
    "scheme": "https",
    "Accept": "application/json, text/plain, */*",
    "Accept-Encoding": "gzip, deflate, br",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    "Content-Length": "512",
    "Content-Type": "application/json;charset=UTF-8",
    "Cookie": "langType=zh_CN; e_cancleAutoLogin=1; JSESSIONID=F80D4421DE667888F09EA13BCCF5E56B",
    "Langtype": "zh_CN",
    "Origin": "https://passport.eteams.cn",
    "Referer": "https://passport.eteams.cn/login?service=https%3A%2F%2Fweapp.eteams.cn%3FcusMenuId%3D5116426542444337800%26urlPageTitle%3D6aaW6aG1",
    "Sec-Ch-Ua": '"Chromium";v="122", "Not(A:Brand";v="24", "Microsoft Edge";v="122"',
    "Sec-Ch-Ua-Mobile": "?0",
    "Sec-Ch-Ua-Platform": "Windows",
    "Sec-Fetch-Dest": "empty",
    "Sec-Fetch-Mode": "cors",
    "Sec-Fetch-Site": "same-origin",
    "Timezoneoffset": "-480",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0",
}

data = {
    "account": "huangmaochun@zwcad.com",
    "registerDataSource": "",
    "registerSource": "",
    "registerSourceUrl": "",
    "moduleSource": "",
    "needPassword": True,
    "password": "J6L66MbHvPmNLD5adIF2afQUTN7gnDYf6uxJiixn8+Zc/fo8m2Ihj19HzPTVb7QxoFMYbaTF1JdJIWabwF6zJhi5/sS+ZDaUwZ0/7IwMW2WdwosbtsEP8bjznnyzHa6AaJHXKYog9FvNfHOzIfFRFcbKZfjpPak+kWG1m+MeG5I=",
    "service": "https://weapp.eteams.cn?cusMenuId=5116426542444337800&urlPageTitle=6aaW6aG1",
    "tenantKey": "all_teams",
    "passportCusLoginDomain": "https://passport.eteams.cn",
    "onlySelfTenant": 0,
}
# %%
# response = requests.post(url, headers=headers, data=data)
session = requests.Session()
response = session.post(url, headers=headers, json=data)

soup = BeautifulSoup(response.text, "html.parser")
form_data = json.loads(soup.text)
redirect_url = form_data["data"]["redirectUrl"]
# %%
response = session.get(redirect_url)
soup = BeautifulSoup(response.text, "html.parser")

# %%
form_url = "https://cdn-static-prod.eteams.cn/build/workflow/static/js/1.js?v=3c887dad"
response = session.get(redirect_url)
soup = BeautifulSoup(response.text, "html.parser")
soup
# %%
