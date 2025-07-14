from rest_framework import serializers
from .models import Reservation, Guest, Room, CheckInAndOut

class RoomSerializer(serializers.ModelSerializer):
    class Meta:
        model = Room
        fields = ['id', 'room_number', 'status', 'room_type']

class RoomUpdateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Room
        fields = ['status']

class GuestSerializer(serializers.ModelSerializer):
    room_number = serializers.CharField(source='room.room_number', default="", read_only=True)
    room_id = serializers.PrimaryKeyRelatedField(
        queryset=Room.objects.all(), source='room', write_only=True, required=False
    )

    class Meta:
        model = Guest
        fields = [
            'id',
            'full_name',
            'phone_number',
            'room_number',
            'room_id'
        ]

class ReservationSerializer(serializers.ModelSerializer):
    guest_name = serializers.CharField(source='guest.full_name', required=False)
    guest_phone = serializers.CharField(source='guest.phone_number', required=False)

    room_number = serializers.CharField(source='room.room_number', default="", read_only=True)
    reservation_status = serializers.CharField(source='status', read_only=True)
    
    guest_id = serializers.PrimaryKeyRelatedField(
        queryset=Guest.objects.all(), source='guest', write_only=True, required=False
    )
    room_id = serializers.PrimaryKeyRelatedField(
        queryset=Room.objects.all(), source='room', write_only=True, required=False
    )

    class Meta:
        model = Reservation
        fields = [
            'id',
            'guest_name',
            'guest_phone',
            'check_in',
            'check_out',
            'room_number',
            'reservation_status',
            'guest_id',
            'status',
            'room_type',
            'room_id'
        ]

class CheckInAndOutSerializer(serializers.ModelSerializer):
    reservation = ReservationSerializer(read_only=True)
    reservation_id = serializers.PrimaryKeyRelatedField(
        queryset=Reservation.objects.all(),
        source='reservation',
        write_only=True
    )

    class Meta:
        model = CheckInAndOut
        fields = [
            'id',
            'reservation',
            'reservation_id',
            'action',
            'timestamp'
        ]

class ReservationUpdateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Reservation
        fields = ['room']
