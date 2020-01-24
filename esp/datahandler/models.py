from django.db import models

class Data(models.Model):
    status=models.CharField(max_length=50)
    pub_date = models.DateTimeField('date published')
    def __str__(self):
        return self.status
        return self.pub_date
class State(models.Model):
    state=models.CharField(max_length=50)
    def __str__(self):
        return self.state
# Create your models here.
