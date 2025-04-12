# Robotic Arm Control with Stepper and Servo Motors

## Project Overview
This project provides a robotic arm control system using an ESP32 microcontroller, stepper motors, and a servo motor. The system is integrated with Blynk for remote control, enabling users to control the arm's position via a mobile app. Additionally, the robotic arm can be controlled using an electromagnet, making it suitable for applications requiring precision movement and object manipulation.

## Features
- Control of two stepper motors for movement in X and Y directions.
- Servo motor control for fine-grained adjustments.
- Integration with Blynk for remote control via a mobile app.
- Control of an electromagnet to pick and drop objects.
- Customizable control parameters (motor angles, delay, etc.).

## Components
- **ESP32 Microcontroller**: The main controller for the robotic arm.
- **Stepper Motors (2)**: Used to control the movement of the robotic arm along two axes.
- **Servo Motor (1)**: Used to control the arm's gripper or additional rotation.
- **Electromagnet**: Used to pick up or release objects when activated.
- **Blynk Mobile App**: For controlling the robotic arm remotely.

## Hardware Setup
1. **ESP32 Pin Connections**:
    - **Step Motor 1 (X-axis)**:
        - IN1_PIN -> D12
        - IN2_PIN -> D13
        - IN3_PIN -> D14
        - IN4_PIN -> D15
    - **Step Motor 2 (Y-axis)**:
        - IN1_PIN_2 -> D4
        - IN2_PIN_2 -> D5
        - IN3_PIN_2 -> D6
        - IN4_PIN_2 -> D7
    - **Servo Motor**:
        - SERVO_PIN -> D0
    - **Electromagnet**:
        - ELECTROMAGNET_PIN -> D8

2. **Power Supply**:
    - Ensure that each motor and the ESP32 are powered properly. Use a 5V power supply for the ESP32, and a suitable power supply for the stepper motors and the servo motor (typically 12V or as per motor specifications).

## Software Setup

### Libraries Required
1. **Blynk**: A library for integrating with the Blynk app.
    - Install via the Arduino Library Manager or download from [Blynk GitHub](https://github.com/blynkkk/blynk-library).
2. **ESP32 Servo**: A library to control servo motors with the ESP32.
    - Install via the Arduino Library Manager or download from [ESP32 Servo GitHub](https://github.com/madcowswe/ESP32Servo).

### Installation Instructions
1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/robotic-arm-control.git
    cd robotic-arm-control
    ```

2. **Install Libraries**:
    - Install the necessary libraries via the Arduino IDE:
        - Blynk Library: Go to `Sketch` > `Include Library` > `Manage Libraries...` and search for "Blynk" to install.
        - ESP32 Servo Library: Go to `Sketch` > `Include Library` > `Manage Libraries...` and search for "ESP32Servo" to install.

3. **Upload Code to ESP32**:
    - Open the `robotic_arm_control.ino` file in the Arduino IDE.
    - Select your ESP32 board from `Tools` > `Board` > `ESP32 Dev Module`.
    - Select the correct port from `Tools` > `Port`.
    - Upload the code to the ESP32.

4. **Blynk App Setup**:
    - Download the Blynk app from the App Store (iOS) or Google Play Store (Android).
    - Create a new project and select ESP32 as the device.
    - Add widgets for controlling the stepper motors, servo motor, and electromagnet:
        - **V1 and V2**: Slider or button to control the stepper motors.
        - **V3**: Slider to control the servo motor.
        - **V4**: Button to control the electromagnet.
    - Copy the **Auth Token** provided by Blynk and paste it into the `BLYNK_AUTH_TOKEN` in the code.

5. **Wi-Fi Setup**:
    - Replace the Wi-Fi credentials (`ssid` and `pass`) with your local Wi-Fi network information.

## Usage
- **Step Motor Control**: Use sliders or buttons in the Blynk app to move the robotic arm along the X and Y axes.
- **Servo Motor Control**: Use a slider in the Blynk app to control the angle of the servo motor.
- **Electromagnet Control**: Use a button in the Blynk app to activate the electromagnet. The electromagnet will pick up objects when activated and release them when deactivated.

## Code Explanation
- **Stepper Motor Control**: The stepper motors are controlled using a basic stepping sequence. The `moveStepMotor` function moves the motor to the target angle based on the number of steps and the direction.
- **Servo Motor Control**: The servo motor is controlled using the `Servo.write()` function, which sets the servo's angle.
- **Electromagnet Control**: The electromagnet is controlled using a simple digital write to the specified pin.

## Customization
- You can adjust the `stepAngle` to change the precision of the stepper motor movement.
- The `stepDelay` variable controls the speed of the motor movement.
- Modify the pin assignments if you want to use different pins for the stepper or servo motors.

## Troubleshooting
- **Problem**: The motors are not moving.
    - **Solution**: Check the wiring of the motors and ensure the power supply is sufficient for the motors.
- **Problem**: The Blynk app is not connecting to the ESP32.
    - **Solution**: Ensure the Wi-Fi credentials are correct and the Blynk Auth Token is pasted correctly in the code.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- Thanks to the Blynk team for their excellent app and library.
- Thanks to the creators of the stepper motor and servo motor libraries.

