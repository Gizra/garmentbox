Feature: Test production order flow
  Test the addition and edit forms of production order nodes.

  @javascript
  Scenario: Viewing the add production-order page, with different Quantity/ Size.
    Given I visit the front page
    And I fill in "Username" with "dummyuser"
    And I fill in "Password" with "dummyuser"
    And I press "Log in"
    And I visit "season/24"
    And I click "Production Orders"
    When I click "Add new production order"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order   | Item variation         | Quantity / Size             | Fabric  | Production cost | Add more items  |
    | <checkbox> checked | Grey v-neck shirt      | Small 18 Medium 20 Large 42 | <image> | $4,000.00       | Add more items  |
    | <checkbox> checked | Lines v-neck shirt     | Small 37 Medium 26 Large 29 | <image> | $2,438.00       | Add more items  |

  @javascript
  Scenario: Viewing the add production-order page with detailed variant information.
    Given I visit the front page
    And I fill in "Username" with "dummyuser"
    And I fill in "Password" with "dummyuser"
    And I press "Log in"
    And I visit "season/24"
    And I click "Production Orders"
    When I click "Add new production order"
    And I click "Grey v-neck shirt"
    And I click "Add more items"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order    | Item variation         | Quantity / Size              | Fabric  | Production cost | Add more items  |
    | <checkbox> checked  | Grey v-neck shirt      | Small 18 Medium 20 Large 42  | <image> | $4,000.00       | Cancel          |
    | <checkbox> checked  | Customer Salty moda    | Small 11 Medium 0 Large 5    |         | $800.00         |                 |
    | <checkbox> checked  | Customer N/A           | Small 0 Medium 0 Large 7     |         | $350.00         |                 |
    | <checkbox> checked  | Customer High Couture  | Small 1 Medium 0 Large 20    |         | $1,050.00       |                 |
    | <checkbox> checked  | Customer N/A           | Small 0 Medium 2 Large 0     |         | $100.00         |                 |
    | <checkbox> checked  | Customer Gap           | Small 5 Medium 0 Large 10    |         | $750.00         |                 |
    | <checkbox> checked  | Customer N/A           | Small 0 Medium 12 Large 0    |         | $600.00         |                 |
    | <checkbox> checked  | Customer N/A           | Small 1 Medium 6 Large 0     |         | $350.00         |                 |
    |                     | Grey v-neck shirt      | Small Medium Large           |         | N/A             |                 |

  @javascript
  Scenario: Testing price re-calculation.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    When I click "Add new production order"
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
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    And I click "Add new production order"
    And I uncheck "Include in order" in row containing "Customer Salty moda" of table "inventory-lines-table"
    And I fill "Small" with "2"
    When I click "edit"
    And I click "Grey v-neck shirt"
    Then the "Include in order" checkbox in row containing "Customer Salty moda" of table "inventory-lines-table" should be unchecked

  @api
  Scenario: Adding an inventory line to a production order and checking that it's not available to other orders.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    And I click "Add new production order"
    And I uncheck "Include in order" in row containing "Customer Salty moda" of table "inventory-lines-table"
    And I click "Save"
    When I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    And I click "Add new production order"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order    | Item variation         | Quantity / Size            | Fabric  | Production cost | Add more items  |
    | <checkbox> checked  | Grey v-neck shirt      | Small 11 Medium 0 Large 5  | <image> | $800.00         | Add more items  |
    | <checkbox> checked  | Customer Salty moda    | Small 11 Medium 0 Large 5  |         | $800.00         |                 |

  @api
  Scenario: Test URL generation for create link.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    When I click "Add new production order"
    Then the URL query "field_season" should have the id of "Autumn-Winter 2013 Women"
