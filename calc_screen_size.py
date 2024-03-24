import math

# Constants for the DFRobot Gravity IR Camera
MAX_DISTANCE_METERS = 3
HORIZONTAL_ANGLE_DEGRESS = 33
VERTICAL_ANGLE_DEGREES = 23

def calc_effective_horizon_length(distance_meters: int):
    return distance_meters * math.tan(math.radians(HORIZONTAL_ANGLE_DEGRESS))

def calc_effective_vertical_length(distance_meters: int):
    return distance_meters * math.tan(math.radians(VERTICAL_ANGLE_DEGREES))

def calc_effective_screen_size_strict_inches(distance_meters: int, screen_ratio: float):
    """
    screen ratio is horizontal/vertical (i.e 16x9, 4x3, etc.)
    the screen surface must be less than a quarter of the effective field of view
    to support tracking the whole screen
    (pointing the middle of the camera to the corner of the screen)
    an optimization to this calculation (which will allow a larger screen) is:
    half of the field of view equals the distance from corner of the screen to the furthest IR sensor
    """
    effective_horizontal_length = calc_effective_horizon_length(distance_meters)
    effective_vertical_length = calc_effective_vertical_length(distance_meters)

    # match vertical view to screen ratio
    matched_vertical = effective_horizontal_length * (1 / screen_ratio)
    matched_horizontal = effective_vertical_length * screen_ratio

    vertical_as_master_matches = False
    if matched_horizontal < effective_horizontal_length:
        vertical_as_master_matches = True

    horizontal_as_master_matches = False
    if matched_vertical < effective_vertical_length:
        horizontal_as_master_matches = True

    if vertical_as_master_matches:
        # calculate screen size
        screen_size_m = math.sqrt((effective_vertical_length ** 2) + (matched_horizontal ** 2))
        vertical_as_master_screen_size_inch = (screen_size_m * 100) / 2.54

    if horizontal_as_master_matches:
        # calculate screen size
        screen_size_m = math.sqrt((matched_vertical ** 2) + (effective_horizontal_length ** 2))
        horizontal_as_master_screen_size_inch = (screen_size_m * 100) / 2.54

    if vertical_as_master_matches and horizontal_as_master_matches:
        # if both matches, return the biggest screen possible
        return max(vertical_as_master_screen_size_inch, horizontal_as_master_screen_size_inch)
    
    if vertical_as_master_matches:
        return vertical_as_master_screen_size_inch
    
    if horizontal_as_master_matches:
        return horizontal_as_master_screen_size_inch
    
    # if we got here, we did something wrong
    print("woops")
    return 0

print(calc_effective_screen_size_strict_inches(1, 4/3))
