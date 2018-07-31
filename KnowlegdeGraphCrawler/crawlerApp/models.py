#_*_coding:utf8_*_

from django.db import models

class Resorce(models.Model):
    name = models.CharField(u'课程名',max_length=30)
    url = models.TextField(u'url') 

def __str__(self):
    return self.Course_name
