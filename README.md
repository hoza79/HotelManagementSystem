# Hotel Management System

This project is a desktop hotel management system built using two main technologies:

- Django REST Framework (Python) as the backend API
- Qt/QML (C++) as the frontend user interface

---

## Project Overview

The hotel management system provides functionality to manage hotel operations including:

- Room management
- Guest management
- Reservation handling
- Check-in and check-out processes

It enables staff to:

- Track room availability and statuses
- Maintain records of guests and reservations
- Perform check-ins and check-outs, updating room statuses and guest assignments accordingly
- View logs of all check-in and check-out activities
- Search and filter across rooms, guests, reservations, and check-in/out records

---

## Features

### Room Management

- List rooms with current statuses: Vacant, Occupied
- Update the status of rooms
- Visual layout of rooms in the frontend

### Guest Management

- Add new guests
- Search and view guest details
- Assign guests to rooms

### Reservation Management

- Create new reservations
- View reservations including check-in and check-out dates
- Prevent duplicate check-ins

### Check-In and Check-Out

- Process guest check-ins and check-outs
- Automatically update room status
- Maintain logs of all check-in and check-out actions
- Filter and search the logs

---

## Technology Stack

### Backend

- Python 3
- Django
- Django REST Framework

### Frontend

- Qt 6
- QML
- C++

---

## How to Run the Project

### Run the Backend (Django)

Install Python dependencies:

```
pip install django djangorestframework
```

Run the development server:

```
python manage.py runserver
```

By default, the backend API will be available at:

```
http://127.0.0.1:8000/
```

---

### Run the Frontend (Qt/QML)

Open the Qt project in Qt Creator or build manually from the command line:

```
qmake
make
./appHotelManagementSystem
```

---

## API Endpoints

Main backend API endpoints include:

- `/api/rooms/`  
- `/api/guests/`  
- `/api/reservations/`  
- `/api/checkinout/`  

See the Django views and serializers for detailed API behavior.

---

## License

MIT License
