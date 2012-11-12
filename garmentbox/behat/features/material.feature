Feature: Test Material page
  Make sure an material page is presented correctly.

 @api @mashau
  Scenario: Basic content is shown on the item page.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "material" page titled "Ivory Satin Button"
    Then I should see the heading "Ivory Satin Button"
    And I should see "120cm"
    And I should see "Wash & Rinse"
    And I should see "cotton 50%"
