from django.shortcuts import render
from django.shortcuts import render_to_response

# Create your views here.
def home(request):
	return render_to_response('home.html')

def ddd(request):
	return render_to_response('ccc.html')