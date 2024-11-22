import requests
import os


def fetch_tle_data(username, password, name, noradid):
    login_url = "https://www.space-track.org/ajaxauth/login"
    tle_url = f"https://www.space-track.org/basicspacedata/query/class/tle_latest/NORAD_CAT_ID/{noradid}/orderby/EPOCH desc/limit/1/format/tle"

    # Construct the file path
    current_directory = os.path.dirname(os.getcwd())
    file_directory = os.path.join(os.path.dirname(current_directory), "resources", "TLE")
    file_path = os.path.join(file_directory, f"{name}.txt")

    # Check if the file already exists
    if os.path.exists(file_path):
        return f"The file '{file_path}' already exists. No action taken."

    try:
        # Create the directory if it does not exist
        os.makedirs(file_directory, exist_ok=True)

        # Start a session
        with requests.Session() as session:
            # Log in to Space-Track
            login_payload = {
                'identity': username,
                'password': password
            }
            login_response = session.post(login_url, data=login_payload)

            if login_response.status_code != 200:
                return f"Login failed. Status code: {login_response.status_code}. Response: {login_response.text}"

            # Fetch the TLE data
            tle_response = session.get(tle_url)

            if tle_response.status_code != 200:
                return f"Failed to retrieve TLE data. Status code: {tle_response.status_code}. Response: {tle_response.text}"

            # Validate response content
            if not tle_response.text.strip():
                return "TLE data response is empty. No data saved."

            # Save TLE data to file
            with open(file_path, 'w') as f:
                f.write(tle_response.text)

            return f"TLE data saved to {file_path}"

    except requests.RequestException as e:
        return f"An error occurred during the network operation: {e}"

    except Exception as e:
        return f"An unexpected error occurred: {e}"