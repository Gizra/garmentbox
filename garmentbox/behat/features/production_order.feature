Feature: Test production order flow
  Test the addition and edit forms of production order nodes.

  @javascript
  Scenario: Viewing the add production-order page, with different Quantity/ Size.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    When I click "Add new production order"
    Then I should see a table identified "inventory-lines-table" with the following <contents>:
    | Include in order   | Item variation         | Quantity / Size                             | Fabric  | Production cost | Add more items  |
    | <checkbox> checked | Grey v-neck shirt      | Small 18 Medium 20 Large 42                 | <image> | <ignore>        | Add more items  |
    | <checkbox> checked | Lines v-neck shirt     | Small 37 Medium 26 Large 29                 | <image> | <ignore>        | Add more items  |

  @javascript
  Scenario: Viewing the add production-order page with detailed variant information.
    Given I am logged in as a user with the "authenticated user" role
    When I visit "node/add/production-order"
    And I click "Grey v-neck shirt"
    And I click "Add more items" under the item "Grey v-neck shirt"
    Then I should see a table with the following <contents>:
    | Include in order   | Item variation         | Quantity / Size                             | Fabric  | Production cost | Add more items  |
    | <checkbox checked> | Grey v-neck shirt      | Small 18 Medium 20 Large 42                 | <image> | $4,000.00       | Cancel          |
    | <checkbox checked> | Customer Salty moda    | Small 11 Medium 0 Large 5                   |         | $800.00         |                 |
    | <checkbox checked> | Customer N/A           | Small 0 Medium 0 Large 7                    |         | $350.00         |                 |
    | <checkbox checked> | Customer High Couture  | Small 1 Medium 0 Large 10                   |         | $1,050.00       |                 |
    | <checkbox checked> | Customer N/A           | Small 0 Medium 2 Large 0                    |         | $100.00         |                 |
    | <checkbox checked> | Customer Gap           | Small 5 Medium 0 Large 5                    |         | $750.00         |                 |
    | <checkbox checked> | Customer N/A           | Small 0 Medium 12 Large 0                   |         | $600.00         |                 |
    | <checkbox checked> | Customer N/A           | Small 1 Medium 6 Large 0                    |         | $350.00         |                 |
    | <checkbox checked> | Grey v-neck shirt      | Small <input> Medium <input> Large <input>  |         | N/A             |                 |

  @javascript
  Scenario: Testing price re-calculation.
    Given I am logged in as a user with the "authenticated user" role
    When I visit "node/add/production-order"
    And I click "Grey v-neck shirt"
    And I uncheck "Include in order" of table row "Customer Salty moda"
    And I fill "Small" with "2"
    Then the "production cost" column of "Grey v-neck shirt" should be "$3,300.00"
    And the "production cost" column of "New item" should be "$100.00"
    And the "Total items" count should be "xx"
    And the "Total price" count should be "xx"

  @api
  Scenario: Testing production order creation and editing.
    Given I am logged in as a user with the "authenticated user" role
    And I visit "node/add/production-order"
    And I click "Grey v-neck shirt"
    And I uncheck "Include in order" of table row "Customer Salty moda"
    And I fill "Small" with "2"
    When I click "edit"
    And I click "Grey v-neck shirt"
    Then the checkbox "76" should be unchecked

  @api
  Scenario: Test URL generation for create link.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    When I click "Add new production order"
    Then the URL query "field_season" should have the id of "Autumn-Winter 2013 Women"
