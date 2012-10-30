Feature: Test Season page
  Make sure a season page is presented correctly.

  @api
  Scenario: Basic content is shown on the season task list page.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    Then I should see the heading "Autumn-Winter 2013 Women"
    And the page status is shown as "Design"
    And I should see the following <links>
    | links         |
    | Task List     |
    | Items         |
    | Inventory     |
    | Orders        |
    | Add new task  |

  @api
  Scenario: Content is shown on the season task list itself.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    Then I should see a table titled "Task list / Item 19" with the following <contents>:
    | Summary             | Status      | Assignee | Replies | Last updated | Created  | Actions |
    | Fix marker          | Needs work  | <ignore> | 0       | <ignore>     | <ignore> | edit    |
    And I should see "Total open tasks: 3"

  @api
  Scenario: Correct content is shown on the season items list.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women", in the tab "items"
    Then I should see a table titled "V-neck shirt" with the following <contents>:
    |         | Variant            | Main material | Status | Retail price | Wholesale price |
    | <image> | Lines v-neck shirt | <image>       | Draft  | $80.00       | $55.00          |

  @api
  Scenario: Correct content is shown on the season inventory list.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women", in the tab "inventory"
    Then I should see a table titled "Inventory summary" with the following <contents>:
    | Variation                   | Small                           | Medium                                        | Large                                 | Type                                                      |
    | Lines v-neck shirt - Total  | 19 Stock 9 Available 13 Ordered | 7 Stock 0 Available 10 Ordered 7 Future stock | 8 Stock 8 Available 11 Future stock   | All types Except of Consignment, Defective, Sent / Sold.  |
    | Lines v-neck shirt          | 15 10 Ordered                   | 9 9 Ordered                                   | 10 10 Ordered                         | Sent / Sold                                               |
    | Lines v-neck shirt          | 19 10 Ordered                   | 7 7 Ordered                                   | 8                                     | Regular stock                                             |
    | Lines v-neck shirt          | 1 1 Ordered                     | 7                                             | 7                                     | Future production                                         |
    | Lines v-neck shirt          | 2 2 Ordered                     | 3 3 Ordered                                   | 4                                     | Current production                                        |

  @api
  Scenario: Correct content is shown on the season orders list.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women", in the tab "orders"
    Then I should see a table titled "Orders" with the following <contents>:
    | Order   | Customer | Total price | Total items | Last delivery date  | Next delivery date    | Status  |
    | order1  | Gap      | N/A         | 49          | N/A                 | Wed, 2013-05-29 21:00 | New     |
    And the order "order1" should have these <inventory lines>
    | Variation           | Small | Medium  | Large | Total | Status              |
    | Black v-neck shirt  | 0     | 6       | 5     | 11    | Current production  |
    | Grey v-neck shirt   | 5     | 0       | 10    | 15    | Consignment         |
    | Lines v-neck shirt  | 5     | 7       | 10    | 22    | Sent / Sold         |
    | Lines v-neck shirt  | 1     | 0       | 0     | 1     | Future production   |
