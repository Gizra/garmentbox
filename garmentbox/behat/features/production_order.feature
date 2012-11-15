Feature: Test production order flow
  Test the addition and edit forms of production order nodes.

  @javascript
  Scenario: Viewing the add production-order page, with different Quantity/ Size.
    Given I am logged in as "user"
    And I visit "season/24"
    And I click "Production Orders"
    When I click "Add new production order"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order   | Item variation         | Small | Medium  | Large | Fabric  | Production cost | Add more items  |
    | <checkbox> checked | Grey v-neck shirt      | 18    | 20      | 42    | <image> | $4,000.00       | Add more items  |
    | <checkbox> checked | Lines v-neck shirt     |       | 43      | 49    | <image> | $2,438.00       | Add more items  |

  @javascript
  Scenario: Viewing the add production-order page with detailed variant information.
    Given I am logged in as "user"
    And I visit "season/24"
    And I click "Production Orders"
    When I click "Add new production order"
    And I click "Grey v-neck shirt"
    And I click "Lines v-neck shirt"
    And I click "Add more items"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order    | Item variation         | Small   | Medium  | Large   | Fabric  | Production cost | Add more items  |
    | <checkbox> checked  | Grey v-neck shirt      | 18      | 20      | 42      | <image> | $4,000.00       | Cancel          |
    | <checkbox> checked  | Customer Salty moda    | 11      |         | 5       |         | $800.00         |                 |
    | <checkbox> checked  | Customer N/A           |         |         | 7       |         | $350.00         |                 |
    | <checkbox> checked  | Customer High Couture  | 1       |         | 20      |         | $1,050.00       |                 |
    | <checkbox> checked  | Customer N/A           |         | 2       |         |         | $100.00         |                 |
    | <checkbox> checked  | Customer Gap           | 5       |         | 10      |         | $750.00         |                 |
    | <checkbox> checked  | Customer N/A           |         | 12      |         |         | $600.00         |                 |
    | <checkbox> checked  | Customer N/A           | 1       | 6       |         |         | $350.00         |                 |
    |                     | New items              | <input> | <input> | <input> |         | $0.00           |                 |

  @javascript
  Scenario: Testing price re-calculation.
    Given I am logged in as "user"
    And I visit "season/24"
    And I click "Production Orders"
    And I click "Add new production order"
    And I click "Grey v-neck shirt"
    When I uncheck "Include in order" in row containing "Customer Salty moda" in table "inventory-lines-table"
    And I click "Add more items"
    And I fill in "Small" with "2" in row containing "New items" in table "inventory-lines-table"
    Then the "Production cost" column of "Grey v-neck shirt" in table "inventory-lines-table" should be "$3,300.00"
    And the "Production cost" column of "New items" in table "inventory-lines-table" should be "$100.00"
    And the "Total items" input should have the value "199"
    And the "Production price" input should have the value "$7,501.00"

  @api @wip
  Scenario: Testing production order creation and editing.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    And I click "Add new production order"
    And I uncheck "Include in order" in row containing "Customer Salty moda" in table "inventory-lines-table"
    And I fill in "Small" with "2" in row containing "New items" in table "inventory-lines-table"
    And I press "Save"
    ## Clicking the first row on the production orders view. The link title should be changed.
    And I click "Production order"
    When I click "Edit"
    Then the "Include in order" checkbox in row containing "Customer Salty moda" in table "inventory-lines-table" should be unchecked

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
