from django.contrib import admin
from .models import Room, Guest, Reservation, CheckInAndOut

@admin.register(Room)
class RoomAdmin(admin.ModelAdmin):
    list_display = ('room_number', 'room_type', 'status')
    list_filter = ('room_type', 'status')
    search_fields = ('room_number',)

@admin.register(Guest)
class GuestAdmin(admin.ModelAdmin):
    list_display = ('full_name', 'phone_number', 'room')
    search_fields = ('full_name', 'phone_number')

    def delete_model(self, request, obj):
        if obj.room:
            obj.room.status = "Vacant"
            obj.room.save()
        super().delete_model(request, obj)

@admin.register(Reservation)
class ReservationAdmin(admin.ModelAdmin):
    list_display = ('guest', 'room_type', 'check_in', 'check_out', 'status')
    list_filter = ('status', 'room_type')
    search_fields = ('guest__full_name',)

    def delete_model(self, request, obj):
        if obj.room:
            obj.room.status = "Vacant"
            obj.room.save()
        super().delete_model(request, obj)

@admin.register(CheckInAndOut)
class CheckInAndOutAdmin(admin.ModelAdmin):
    list_display = ('reservation', 'action', 'timestamp')
    list_filter = ('action',)
