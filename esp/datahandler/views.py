from django.shortcuts import render
from django.template import Context, loader
from django.http import *
from .models import Data,State
from django.views.decorators.csrf import csrf_exempt
from datetime import datetime

# Create your views here.
@csrf_exempt
def index(request):
    if request.method == "POST":
        status=request.POST.get("status")
        p=Data(status=status,pub_date=datetime.now())
        p.save()
        Data.objects.all()[0].delete()
        return HttpResponse("Got your data")
        
    if request.method=="GET":
        alldata=Data.objects.all()
        recent=Data.objects.all().last()
        context={'alldata':alldata,
                'recent':recent}
        return render(request, 'datahandler/index.html', context)
    
@csrf_exempt
def switch(request):
    if request.method=="POST":
         if request.POST.get("condition")=="on":
             condition=request.POST.get("condition")
             p=State(state=condition)
             p.save()
             State.objects.all()[0].delete()
         elif request.POST.get("condition")=="off":
             condition=request.POST.get("condition")
             p=State(state=condition)
             p.save()
             State.objects.all()[0].delete()
         return HttpResponse(State.objects.all().last())
         






