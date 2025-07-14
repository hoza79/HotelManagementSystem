# models.py

from django.db import models
from django.db.models.signals import post_delete
from django.dispatch import receiver

class Room(models.Model):
    ROOM_TYPES = (
        ('Single', 'Single'),
        ('Double', 'Double'),
        ('Suite', 'Suite'),
    )
    STATUS_CHOICES = (
        ('Vacant', 'Vacant'),
        ('Occupied', 'Occupied'),
        ('Dirty', 'Dirty'),
        ('Out of Order', 'Out of Order'),
    )

    room_number = models.CharField(max_length=20, unique=True)
    room_type = models.CharField(max_length=20, choices=ROOM_TYPES)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='Vacant')

    def __str__(self):
        return self.room_number

class Guest(models.Model):
    full_name = models.CharField(max_length=255, unique=True)
    phone_number = models.CharField(max_length=50)
    room = models.ForeignKey(Room, on_delete=models.SET_NULL, null=True, blank=True)

    def __str__(self):
        return self.full_name

class Reservation(models.Model):
    STATUS_CHOICES = (
        ('Pending', 'Pending'),
        ('Checked-in', 'Checked-in'),
        ('Completed', 'Completed'),
    )

    guest = models.ForeignKey(Guest, on_delete=models.CASCADE)
    room = models.ForeignKey(Room, on_delete=models.SET_NULL, null=True, blank=True)
    check_in = models.DateTimeField()
    check_out = models.DateTimeField()
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='Pending')
    room_type = models.CharField(max_length=50, default="Single")

    def __str__(self):
        return f"Reservation {self.id} - {self.guest.full_name}"

class CheckInAndOut(models.Model):
    ACTION_CHOICES = (
        ('IN', 'IN'),
        ('OUT', 'OUT'),
    )
    reservation = models.ForeignKey(Reservation, on_delete=models.CASCADE)
    action = models.CharField(max_length=3, choices=ACTION_CHOICES)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.reservation} - {self.action}"

# SIGNALS to free up rooms on delete

@receiver(post_delete, sender=Guest)
def free_room_on_guest_delete(sender, instance, **kwargs):
    if instance.room:
        instance.room.status = "Vacant"
        instance.room.save()

@receiver(post_delete, sender=Reservation)
def free_room_on_reservation_delete(sender, instance, **kwargs):
    if instance.room:
        instance.room.status = "Vacant"
        instance.room.save()
