from django.urls import path
from .views import (
    ReservationList,
    ReservationCreate,
    GuestList,
    GuestCreate,
    RoomList,
    CheckInAndOutList,
    CheckInAndOutCreate,
    RoomUpdate,
    ReservationUpdateView,
    GuestSearchView,
)

urlpatterns = [
    path('api/reservations/', ReservationList.as_view(), name='reservation-list'),
    path('api/reservations/create/', ReservationCreate.as_view(), name='reservation-create'),
    path('api/guests/', GuestList.as_view(), name='guest-list'),
    path('api/guests/create/', GuestCreate.as_view(), name='guest-create'),
    path('api/guests/search/', GuestSearchView.as_view(), name='guest-search'),
    path('api/rooms/', RoomList.as_view(), name='room-list'),
    path('api/checkinout/', CheckInAndOutList.as_view(), name='checkinout-list'),
    path('api/checkinout/create/', CheckInAndOutCreate.as_view(), name='checkinout-create'),
    path('api/rooms/<int:pk>/update/', RoomUpdate.as_view(), name='room-update'),
    path('api/reservations/<int:pk>/update/', ReservationUpdateView.as_view(), name='reservation-update'),
]
