# coding=utf-8
# 爬取 菜鸟教程（wwww.runoob.com）

from urllib import request
from pyquery import PyQuery as pq
import os
import gzip
import pdfkit

pdf_key=pdfkit.configuration(wkhtmltopdf= r"D:\软件王国\wkhtmltopdf\bin\wkhtmltopdf.exe")
# 配置文件信息


config = {
    'url': 'http://www.runoob.com',
    'htmlSavePath': './PDF/',
    'retime': 10,
    'kinds': [
        '/django/django-tutorial.html',
       '/git/git-tutorial.html',
       '/html/html5-intro.html',
       '/jquery/jquery-tutorial.html',
       '/css/css-tutorial.html',
    '/nodejs/nodejs-tutorial.html',
         '/cplusplus/cpp-tutorial.html',
       '/php/php-tutorial.html',
   '/ruby/ruby-tutorial.html',
      '/angularjs/angularjs-tutorial.html',
       # '/python/python-tutorial.html',
      #  '/cplusplus/cpp-tutorial.html',
       # '/js/js-tutorial.html',
      #  '/go/go-tutorial.html',
    ],

    'h': {
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0",
        "Accept-Language": "zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3",
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Encoding": "gzip, deflate"
    },
    'htmlHead': """
        <!DOCTYPE html>
        <html>
        <head>
          <title></title>
          <meta charset="utf-8" />
          <link rel="stylesheet" href="http://www.runoob.com/wp-content/themes/runoob/style.css?v=1.07" type="text/css" media="all" />
        </head>
        <body style="width: 1080px;margin: 10px auto;">
            """,
    'htmlFoot': """
        </body>
        </html>
            """
}
# 获取url连接池


def getUrlLinks(url):
    global config
    Urls = []           # 连接池
    httpf = request.Request(url, headers=config['h'])
    try:
        reqL = request.urlopen(httpf, timeout=30)
    except:
        return False
    else:
        content = reqL.read()
    finally:
        try:
            reqL.close()
        except:
            return False
    # Query 操作
    # con = content.decode("utf-8")
    con = gzip.decompress(content).decode("utf-8")  # 解压网页数据
    dom = pq(con)                        # 初始化Query操作
    title = dom('title').text()          # 筛选当前页面的标题<title>
    dom = dom('div#leftcolumn')
    dom = dom('a')
    dom = dom.make_links_absolute(base_url=config['url'])  # 将相对链接转换为绝对链接
    for one in dom.items():              # 遍历所有筛选出来的 pyQuery对象获取其href属性
        Urls.append(one.attr('href'))
    return Urls, title                    # 返回连接池及标题
# 获取网页内正文并返回html格式文本


def url2con(url):
    global config
    httpf = request.Request(url, headers=config['h'])
    try:
        reqL = request.urlopen(httpf, timeout=30)
        content = reqL.read()
    except:
        return False
    finally:
        try:
            reqL.close()
        except:
            return False
    # con = content.decode("utf-8")
    con = gzip.decompress(content).decode("utf-8")  # 解压网页数据
    # Query 操作 筛选内容
    dom = pq(con)
    tit = dom('title').text()
    dom = dom('div.article-body')
    dom = dom.make_links_absolute(base_url=config['url'])  # 将相对链接转换为绝对链接
    con = dom.html()
    return con, tit
# 超时重连函数


def reLink(fun, para, retime=5):
    con = fun(para)
    i = 0
    while retime and (con == False):
        i += 1
        con = fun(para)
        print("miss url(%s) reLink %d " % (para, i))
        retime -= 1
    return con


def main():
    global config
    if not os.path.isdir(config['htmlSavePath']):
        os.makedirs(config['htmlSavePath'])


    for kind in config['kinds']:
        getPath = config['url'] + kind
        res = reLink(getUrlLinks, getPath, 20)
        if res == False:
            print('请求资源失败，请稍后重试！')
            exit(0)
        else:
            urls, title = res
        # html 暂存路径

        print('work in 【%s】(url:%s)' % (title, getPath))  # 提示信息
        title = title.split('|')[0].strip()
        tempHtmlPath = config['htmlSavePath'] + title + '.html'
        print("saved %s" % tempHtmlPath)  # 提示信息
        # 先写头部信息
        with open(tempHtmlPath, 'w', encoding="utf-8") as fp:
            fp.write(config["htmlHead"])
        for oneurl in urls:
            i = urls.index(oneurl)
            con = reLink(url2con, oneurl, config['retime'])   # 超时重连
            if con == False:
                continue
            else:
                con = con[0]
            with open(tempHtmlPath, 'a', encoding="utf-8") as fp:
                fp.write(con)
            print('(%d/%d)' % (len(urls), i + 1))  # 进度信息
        # 写尾信息
        with open(tempHtmlPath, 'a', encoding="utf-8") as fp:
            fp.write(config["htmlFoot"])

        print('开始转换为PDF')
        options = {

        'page-size': 'Letter',

        'margin-top': '0.75in',

        'margin-right': '0.75in',

        'margin-bottom': '0.75in',

        'margin-left': '0.75in',

        'encoding': "UTF-8",

        'custom-header': [('Accept-Encoding', 'gzip')],

        'cookie': [

            ('cookie-name1', 'cookie-value1'),

            ('cookie-name2', 'cookie-value2'),

        ],

        'outline-depth': 10,

    }
      
        pdfkit.from_file(tempHtmlPath, config['htmlSavePath'] + title + '.pdf',options=options,configuration=pdf_key)

        print("转换pdf并保存成功！")



if __name__ == '__main__':
    main()