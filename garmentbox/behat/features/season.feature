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
     Then the following <row> should appear in the table "orders" :
      | order3  | High Couture | N/A         | 26 | N/A | <date> 5/30/2013 | Shipping |
      And the order "order3" should have these <inventory lines>
      | Variation          | Small | Medium | Large | Total | Status             |
      | Grey v-neck shirt  | 1     | 0      | 20    | 21    | Future production  |
      | Lines v-neck shirt | 0     | 4      | 1     | 5     | Current production |

  @api @wip
  Scenario: Verify redirections from the front page to the season items tab.
    Given I am logged in as a user from "Imanimo"
      And I go to create "season" node page
      And I fill in "Title" with "Test season"
      # Temp fix: The company should not be selected by the user.
      And I select "Imanimo" from "Company"
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

  @api
  Scenario: Test page display for line sheet list.
    Given I am logged in as a user with the "authenticated user" role
     When I am on a "season" page titled "Autumn-Winter 2013 Women", in the tab "line-sheet"
    Then the table "prices" should have the following <contents>:
      | Wholesale        | Retail           |
      | $55.00 - $70.00  | $80.00 - $100.00 |
     And the table "variants" should have the following <contents>:
      | Name               | Material | Sizes         |
      | Lines v-neck shirt | <image>  | Medium, Large |
      | Black v-neck shirt | <image>  | Small, Medium |

  @api
  Scenario: Test addition of line sheet items.
    Given I am logged in as a user with the "authenticated user" role
     When I add an item variant titled "Grey v-neck shirt" to line sheet
      And I am on a "season" page titled "Autumn-Winter 2013 Women", in the tab "line-sheet"
    Then the table "prices" should have the following <contents>:
      | Wholesale        | Retail               |
      | $55.00 - $70.00  | $55.00 - $100.00     |
     And the table "variants" should have the following <contents>:
      | Name               | Material | Sizes                |
      | Lines v-neck shirt | <image>  | Medium, Large        |
      | Black v-neck shirt | <image>  | Small, Medium        |
      | Grey v-neck shirt  | <image>  | Small, Medium, Large |
