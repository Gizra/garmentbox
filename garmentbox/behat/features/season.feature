Feature: Test Season page
  Make sure a season page is presented correctly.

  @api
  Scenario: Basic content is shown on the season task list page.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the default "season" page
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
     When I am on the default "season" page
     Then the table "view-task-list" should have the following <contents>:
      | Summary             | Status      | Assignee | Replies | Last updated | Created  | Actions |
      | First task          | Open        | <ignore> | 0       | <ignore>     | <ignore> | edit    |
      And I should see "Total open tasks: 3"

  @api
  Scenario: Correct content is shown on the season items list.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the "Season items" page of the default "season"
     Then I should see a table titled "V-neck shirt" with the following <contents>:
      | Variant                    | Main material | Status     | Retail price | Wholesale price |
      | <image> Black v-neck shirt | <image>       | Needs work | $100.00      | $70.00          |

  @api
  Scenario: Correct content is shown on the season inventory list.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the "Season inventory" page of the default "season"
     Then the table "inventory-summary" should have the following <contents>:
      | Variation                   | Small               | Medium                                          | Large                                           | Type                                                      |
      | Lines v-neck shirt - Total  | 0 Stock 0 Available | 12 Stock 0 Available 13 Ordered 7 Future stock  | 22 Stock 17 Available 5 Ordered 11 Future stock | All types Except of Defective, Consignment, Sent / Sold.  |

  @api
  Scenario: Correct content is shown on the season orders list.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the "Season orders" page of the default "season"
     Then the table "orders" should have the following <contents>:
      | Order   | Customer | Total price | Total items | Last delivery date  | Next delivery date | Status  |
      | order1  | Gap      | N/A         | 49          | N/A                 | <date> 5/30/2013   | New     |
    And the order "order1" should have these <inventory lines>
      | Variation           | Small | Medium  | Large | Total | Status              |
      | Black v-neck shirt  | 0     | 6       | 5     | 11    | Current production  |
      | Grey v-neck shirt   | 5     | 0       | 10    | 15    | Consignment         |
      | Lines v-neck shirt  | 0     | 12      | 10    | 22    | Sent / Sold         |
      | Lines v-neck shirt  | 0     | 1       | 0     | 1     | Future production   |

  @api
  Scenario: Verify redirections from the front page to the season items tab.
    Given I am logged in as a user with the "authenticated user" role
      And I go to create "season" node page
      And I fill in "Title" with "Test season"
      And I press "Save"
      When I visit the front page
      Then I should be on a page titled "Test season - Items | Site-Install"

  @api
  Scenario: Verify redirections from the front page to the season tasks tab.
    Given I am logged in as a user with the "authenticated user" role
      And I go to create "season" node page
     When I fill in "Title" with "Test season 2"
      And I press "Save"
      And I click "Items"
      And I click "Add new item"
      And I fill in "Title" with "Test item"
      And I press "Save"
      And I fill in "Title" with "Test item variant"
      And I press "Save"
      And I visit the front page
     Then I should be on a page titled "Test season 2 - Tasks | Site-Install"
