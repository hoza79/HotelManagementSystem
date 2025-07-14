from django.shortcuts import render
from rest_framework import generics, status
from rest_framework.response import Response
from rest_framework import serializers
from .models import Reservation, Guest, Room, CheckInAndOut
from .serializers import (
    ReservationSerializer,
    GuestSerializer,
    RoomSerializer,
    RoomUpdateSerializer,
    CheckInAndOutSerializer,
    ReservationUpdateSerializer,
)

class ReservationList(generics.ListAPIView):
    serializer_class = ReservationSerializer

    def get_queryset(self):
        search = self.request.query_params.get("search", "")
        if search:
            return Reservation.objects.filter(guest__full_name__icontains=search)
        return Reservation.objects.all()

class ReservationCreate(generics.CreateAPIView):
    queryset = Reservation.objects.all()
    serializer_class = ReservationSerializer

    def create(self, request, *args, **kwargs):
        guest_id = request.data.get("guest_id")
        guest_name = request.data.get("guest_name")
        guest_phone = request.data.get("guest_phone")

        if not guest_id:
            guest = Guest.objects.filter(full_name=guest_name).first()
            if not guest:
                guest = Guest.objects.create(
                    full_name=guest_name,
                    phone_number=guest_phone
                )
            guest_id = guest.id

        mutable_data = request.data.copy()
        mutable_data["guest_id"] = guest_id

        serializer = self.get_serializer(data=mutable_data)
        serializer.is_valid(raise_exception=True)
        self.perform_create(serializer)

        headers = self.get_success_headers(serializer.data)
        return Response(serializer.data, status=status.HTTP_201_CREATED, headers=headers)

class ReservationUpdateView(generics.UpdateAPIView):
    queryset = Reservation.objects.all()
    serializer_class = ReservationUpdateSerializer

class GuestList(generics.ListAPIView):
    serializer_class = GuestSerializer

    def get_queryset(self):
        search = self.request.query_params.get("search", "")
        if search:
            return Guest.objects.filter(full_name__icontains=search)
        return Guest.objects.all()

    def list(self, request, *args, **kwargs):
        queryset = self.get_queryset()
        serializer = self.get_serializer(queryset, many=True)
        return Response(serializer.data)

class GuestCreate(generics.CreateAPIView):
    queryset = Guest.objects.all()
    serializer_class = GuestSerializer

    def create(self, request, *args, **kwargs):
        full_name = request.data.get("full_name")
        phone_number = request.data.get("phone_number")

        existing_guest = Guest.objects.filter(full_name=full_name).first()
        if existing_guest:
            existing_guest.phone_number = phone_number
            existing_guest.save()
            serializer = self.get_serializer(existing_guest)
            return Response(serializer.data, status=status.HTTP_200_OK)

        return super().create(request, *args, **kwargs)

class GuestSearchView(generics.ListAPIView):
    serializer_class = GuestSerializer

    def get_queryset(self):
        search = self.request.query_params.get("search", "")
        return Guest.objects.filter(full_name__icontains=search)

class RoomList(generics.ListAPIView):
    serializer_class = RoomSerializer

    def get_queryset(self):
        search = self.request.query_params.get("search", "")
        if search:
            return Room.objects.filter(room_number__icontains=search)
        return Room.objects.all()

class RoomUpdate(generics.UpdateAPIView):
    queryset = Room.objects.all()
    serializer_class = RoomUpdateSerializer

class CheckInAndOutList(generics.ListAPIView):
    serializer_class = CheckInAndOutSerializer

    def get_queryset(self):
        search = self.request.query_params.get("search", "")
        if search:
            return CheckInAndOut.objects.filter(
                reservation__guest__full_name__icontains=search
            )
        return CheckInAndOut.objects.all()

class CheckInAndOutCreate(generics.CreateAPIView):
    queryset = CheckInAndOut.objects.all()
    serializer_class = CheckInAndOutSerializer

    def perform_create(self, serializer):
        instance = serializer.save()

        room_id = self.request.data.get("room_id")
        action = self.request.data.get("action")

        if action == "IN":
            if not room_id:
                raise serializers.ValidationError("Check-In requires a room.")

        try:
            reservation = instance.reservation
            guest = reservation.guest

            if action == "IN":
                reservation.room_id = room_id
                reservation.status = "Checked-in"
                reservation.save()

                guest.room_id = room_id
                guest.save()

                room = Room.objects.get(id=room_id)
                room.status = "Occupied"
                room.save()

            elif action == "OUT":
                old_room = reservation.room
                reservation.status = "Completed"
                reservation.room = None
                reservation.save()

                guest.room = None
                guest.save()

                if old_room:
                    old_room.status = "Vacant"
                    old_room.save()

        except (Reservation.DoesNotExist, Room.DoesNotExist):
            pass
