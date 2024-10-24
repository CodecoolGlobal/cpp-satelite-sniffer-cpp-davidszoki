import requests
import os
from pathlib import Path


def fetch_tle_data(username, password):
    # Space-Track.org login credentials
    login_url = "https://www.space-track.org/ajaxauth/login"
    tle_url = "https://www.space-track.org/basicspacedata/query/class/tle/NORAD_CAT_ID/25544/orderby/EPOCH%20desc/limit/1000/format/tle"

    # Get the current working directory and file path
    current_directory = os.path.dirname(os.getcwd())
    file_path = os.path.join(os.path.dirname(current_directory), "resources", "iss_tle_last_1000.txt")

    # Check if the file already exists
    if os.path.exists(file_path):
        return f"The file '{file_path}'\nalready exists. No action taken."
    else:
        # Start a session to persist the login
        session = requests.Session()

        # Login payload
        login_payload = {
            'identity': username,
            'password': password
        }

        # Log in to Space-Track
        login_response = session.post(login_url, data=login_payload)

        # Check if login was successful
        if login_response.status_code == 200:
            # Now that we are logged in, request the TLE data
            tle_response = session.get(tle_url)

            # Check if TLE request was successful
            if tle_response.status_code == 200:
                # Save the TLE data to the current working directory
                with open(file_path, 'w') as f:
                    f.write(tle_response.text)
                return f"TLE data saved to {file_path}"
            else:
                return f"Failed to retrieve TLE data. Status code: {tle_response.status_code}"
        else:
            return f"Login failed. Status code: {login_response.status_code}"
