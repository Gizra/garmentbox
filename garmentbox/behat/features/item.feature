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
    Then I should see a table titled "Task list" with the following <contents>:
    | Summary             | Status      | Assignee | Replies | Last updated | Created  | Actions |
    | Fix marker          | Needs work  | <ignore> | 0       | <ignore>     | <ignore> | edit    |
    And I should see "Total open tasks: 2"

  @javascript @ww
  Scenario: Correct content is shown on the item inventory list.
    Given I am logged in as "user"
    And I visit "/item/35"
    When I click the row of "Lines v-neck shirt - Total"
    Then I should see a table titled "Inventory summary" with the following <contents>:
    | Variation                   | Small               | Medium                                          | Large                                           | Type                                                      |
    | Lines v-neck shirt - Total  | 0 Stock 0 Available | 12 Stock 0 Available 17 Ordered 7 Future stock  | 22 Stock 17 Available 6 Ordered 11 Future stock | All types Except of Consignment, Defective, Sent / Sold.  |
    | Lines v-neck shirt          | 0                   | 19 14 Ordered                                   | 15 15 Ordered                                   | Sent / Sold                                               |
    | Lines v-neck shirt          | 0                   | 12 12 Ordered                                   | 22 5 Ordered                                    | Regular stock                                             |
    | Lines v-neck shirt          | 0                   | 9 1 Ordered                                     | 7                                               | Future production                                         |
    | Lines v-neck shirt          | 0                   | 4 4 Ordered                                     | 5 1 Ordered                                     | Current production                                        |
