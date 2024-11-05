import requests
import os


def fetch_tle_data(username, password):
    login_url = "https://www.space-track.org/ajaxauth/login"
    tle_url = "https://www.space-track.org/basicspacedata/query/class/tle/NORAD_CAT_ID/25544/orderby/EPOCH%20desc/limit/1000/format/tle"

    current_directory = os.path.dirname(os.getcwd())
    file_path = os.path.join(os.path.dirname(current_directory), "resources", "iss_tle_last_1000.txt")

    if os.path.exists(file_path):
        return f"The file '{file_path}'\nalready exists. No action taken."
    else:
        session = requests.Session()

        login_payload = {
            'identity': username,
            'password': password
        }

        login_response = session.post(login_url, data=login_payload)

        if login_response.status_code == 200:
            tle_response = session.get(tle_url)

            if tle_response.status_code == 200:
                with open(file_path, 'w') as f:
                    f.write(tle_response.text)
                return f"TLE data saved to {file_path}"
            else:
                return f"Failed to retrieve TLE data. Status code: {tle_response.status_code}"
        else:
            return f"Login failed. Status code: {login_response.status_code}"
