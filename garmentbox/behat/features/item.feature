Feature: Test Item page
  Make sure an item page is presented correctly.

  @api
  Scenario: Basic content is shown on the item page.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "item" page titled "V-neck shirt"
    Then I should see the heading "V-neck shirt"
    And the page status is shown as "Draft"
    And I should see the following <links>
    | links               |
    | Main                |
    | Lines v-neck shirt  |
    | Black v-neck shirt  |
    | Grey v-neck shirt   |
    | Add new variation   |

  @api
  Scenario: Content is shown on the task list.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "item" page titled "V-neck shirt"
    Then I should see a table titled "Task list / Item 30" with the following <contents>:
    | Summary             | Status      | Assignee | Replies | Last updated | Created  | Actions |
    | Fix marker          | Needs work  | <ignore> | 0       | <ignore>     | <ignore> | edit    |
    And I should see "Total open tasks: 2"

  @api
  Scenario: Correct content is shown on the item inventory list.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women", in the tab "inventory"
    Then I should see a table titled "Inventory summary" with the following <contents>:
    | Variation                   | Small                           | Medium                                        | Large                                 | Type                                                      |
    | Lines v-neck shirt - Total  | 19 Stock 9 Available 13 Ordered | 7 Stock 0 Available 10 Ordered 7 Future stock | 8 Stock 8 Available 11 Future stock   | All types Except of Consignment, Defective, Sent / Sold.  |
    | Lines v-neck shirt          | 15 10 Ordered                   | 9 9 Ordered                                   | 10 10 Ordered                         | Sent / Sold                                               |
    | Lines v-neck shirt          | 19 10 Ordered                   | 7 7 Ordered                                   | 8                                     | Regular stock                                             |
    | Lines v-neck shirt          | 1 1 Ordered                     | 7                                             | 7                                     | Future production                                         |
    | Lines v-neck shirt          | 2 2 Ordered                     | 3 3 Ordered                                   | 4                                     | Current production                                        |
