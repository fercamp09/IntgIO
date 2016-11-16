from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse

def index(request):
	#return HttpResponse("prueba de proy")
	return render(request, "index_objects.html")
	#return render_to_response('index_objects.html', locals(), context_instance = RequestContext(request))
