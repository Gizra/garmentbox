Feature: Test Material page
  Make sure an material page is presented correctly.

 @api
  Scenario: Basic content is shown on the item page.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "material" page titled "Novelle Art Noveau Natural Shell Buttons"
    Then I should see the heading "Novelle Art Noveau Natural Shell Buttons"
    And I should see a table titled "Task list" with the following <contents>:
      | Summary  | Status     | Assignee | Replies | Last updated | Created  | Actions |
      | Buy more | Needs work |          | 0       | <ignore>     | <ignore> | edit    |
      | Clean    | Open       |          | 0       | <ignore>     | <ignore> | edit    |
    And I should see a table titled "Source info" with the following <contents>:
      | Vendor               | Price  | Length conversion | Unit     | Length unit | Operations  |
      | Vogue Fabrics        | $10.00 | 20.00             | Kilogram | Meter       | Edit Delete |
      | Vogue Fabrics        | $20.00 | 10.00             | Kilogram | Meter       | Edit Delete |
      | High Fashion Fabrics | $30.00 | 10.00             | Kilogram | Meter       | Edit Delete |
    And I should see the following <contents>:
      | Total open tasks: 2 | Rinse in cold water | Plastic 100% | 3.00 | Button |

 @api
  Scenario: Task is added correctly to a material.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "material" page titled "Novelle Art Noveau Natural Shell Buttons"
    And I click "Add new task"
    And I fill in "Title" with "Check for imperfections"
    And I fill in "Body" with "Material might be faulty, needs to be checked."
    And I select "Open" from "Status"
    And I select "Novelle Art Noveau Natural Shell Buttons" from "Reference"
    And I press "Save"
    When I am on a "material" page titled "Novelle Art Noveau Natural Shell Buttons"
    Then I should see a table titled "Task list" with the following <contents>:
      | Summary                 | Status     | Assignee | Replies | Last updated | Created  | Actions |
      | Buy more                | Needs work |          | 0       | <ignore>     | <ignore> | edit    |
      | Clean                   | Open       |          | 0       | <ignore>     | <ignore> | edit    |
      | Check for imperfections | Open       | <ignore> | 0       | <ignore>     | <ignore> | edit    |
    And I should see "Total open tasks: 3"
