#include "GameMetrics.h"

void GameMetrics::GetFPSandFrameTime()
{
    float startTime{ m_Clock.getElapsedTime().asSeconds() * 1000.0f }; // Get start time.
    float timeSinceLast{ startTime - m_LastSampleTime }; // Calculate time passed since the function was last called.

    m_FrameCounter++; // Increment the frame counter every frame.

    if (timeSinceLast >= m_UpdateTime) // Check if we've exceeded the updateTime. UpdateTime is the time window that we want to count frames within.
    {
        m_FPS = (m_FrameCounter * 1000.0f) / timeSinceLast; // Calculate fps by multiplying the frame counter by 1000, going from ms to s. Then divide the result by the time since we last calculated it.
        m_FrameTime = timeSinceLast / m_FrameCounter; // Calculate the average time taken for a single frame to be rendered.

        m_LastSampleTime = startTime; // Set the lastSampleTime to the current startTime.
        m_FrameCounter = 0; // Reset the frame counter.
    }
}

void GameMetrics::Update(Window& window)
{
    GetFPSandFrameTime();

    // Limit FPS if Needed.
    if (m_UpdateLimit) // Check if we need to update the FPS limit.
    {
        if (m_LimitFPS) // Check if we need to keep the FPS limited, but change the value.
            window.GetSFWindow().setFramerateLimit((unsigned int)m_MaxFPS); // Update the max FPS.
        else // Remove the FPS limit when the Limit FPS checkbox is unchecked.
        {
            window.GetSFWindow().setFramerateLimit(0); // Remove FPS limit by setting the limit to 0.
            m_UpdateLimit = false; // Stop trying to update the FPS limit.
            m_LimitFPS = false; // Set trying to limit the FPS.
        }
    }
}