//
//  Camera.cpp
//  Opengl_Mac08_Light
//
//  Created by yujunzhen on 2018/8/3.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <stdio.h>
#ifndef CAMERA_H
#define CAMERA_H
#include <vmath.h>
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW  = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    vmath::vec3 Position;
    vmath::vec3 Front;
    vmath::vec3 Up;
    vmath::vec3 Right;
    vmath::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    Camera(vmath::vec3 position = vmath::vec3(0.0f,0.0f, 0.0f), vmath::vec3 up = vmath::vec3(0.0f, 1.0f, -0.0f), float yaw = YAW, float pitch = PITCH) : Front(vmath::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(vmath::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = vmath::vec3(posX, posY, posZ);
        WorldUp = vmath::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    
    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    vmath::mat4 GetViewMatrix()
    {
        return vmath::lookat(Position,Position + Front, Up);
    }
    
    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }
    
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        
        Yaw   += xoffset;
        Pitch += yoffset;
        
        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        
        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    
    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }
    
private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        vmath::vec3 front;
        front[0] = cos(vmath::radians(Yaw)) * cos(vmath::radians(Pitch));
        front[1] = sin(vmath::radians(Pitch));
        front[2] = sin(vmath::radians(Yaw)) * cos(vmath::radians(Pitch));
//        Front = vmath::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = vmath::normalize(vmath::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = vmath::normalize(vmath::cross(Right, Front));
    }
};



#endif
