# Generated by Django 3.0.1 on 2020-01-07 18:06

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('datahandler', '0002_auto_20200107_1701'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='data',
            name='station',
        ),
    ]
