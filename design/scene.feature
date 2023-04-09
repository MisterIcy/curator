Feature: Scenes
    Background:
        Given I have an open project
    # Describing Scenes
    Scenario: Create a new scene
        When I go to scene creation
        And I set a name
        Then A new scene is created
        And I can see the scene in the list of scenes.

    Scenario: Open a scene
        When I view the list of scenes 
        And I open a scene 
        Then the scene is presented to me

    Scenario: Add a summary to a scene
        When I open a scene
        And I add a summary
        And I save the scene
        Then the scene has a summary 
