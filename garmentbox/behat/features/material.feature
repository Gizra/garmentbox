Feature: Test Material page
  Make sure an material page is presented correctly.

 @api
  Scenario: Basic content is shown on the item page.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "material" page titled "Novelle Art Noveau Natural Shell Buttons"
    Then I should see the heading "Novelle Art Noveau Natural Shell Buttons"
    And I should see "Rinse in cold water"
    And I should see "Plastic 100%"
    And I should see "3.00"
    And I should see "Button"
