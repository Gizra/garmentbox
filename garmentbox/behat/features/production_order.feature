Feature: Test production order flow
  Test the addition and edit forms of production order nodes.

  @javascript
  Scenario: Viewing the add production-order page, with different Quantity/ Size.
    Given I am logged in as "user"
    And I visit "season/24"
    And I click "Production Orders"
    When I click "Add new production order"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order   | Item variation                   | Small   | Medium  | Large   | Fabric  | Production cost |
    | <checkbox> checked | Grey v-neck shirt                | 1       | 2       | 20      | <image> | $1,150.00       |
    | <checkbox>         | Grey v-neck shirt - Extra items  | <input> | <input> | <input> |         | $0.00           |
    | <checkbox> checked | Lines v-neck shirt               |         | 8       | 7       | <image> | $397.50         |

  @javascript
  Scenario: Viewing the add production-order page with detailed variant information.
    Given I am logged in as "user"
    And I visit "season/24"
    And I click "Production Orders"
    When I click "Add new production order"
    And I click "Grey v-neck shirt"
    When I check "Include in order" in row containing "Grey v-neck shirt - Extra items" in table "inventory-lines-table"
    Then the table "inventory-lines-table" should have the following <contents>:
    | Include in order    | Item variation                  | Small   | Medium  | Large   | Fabric  | Production cost |
    | <checkbox> checked  | Grey v-neck shirt               | 1       | 2       | 20      | <image> | $1,150.00       |
    | <checkbox> checked  | Customer High Couture           | 1       |         | 20      |         | $1,050.00       |
    | <checkbox> checked  | Customer N/A                    |         | 2       |         |         | $100.00         |
    | <checkbox>          | Grey v-neck shirt - Extra items | <input> | <input> | <input> |         | $0.00           |

  @javascript
  Scenario: Testing price re-calculation.
    Given I am logged in as "user"
    And I visit "season/24"
    And I click "Production Orders"
    And I click "Add new production order"
    And I click "Grey v-neck shirt"
    When I uncheck "Include in order" in row containing "Customer High Couture" in table "inventory-lines-table"
    When I click "Include in order" in row containing "Grey v-neck shirt - Extra items" in table "inventory-lines-table"
    And I fill in "Small" with "2" in row containing "Grey v-neck shirt - Extra items" in table "inventory-lines-table"
    Then the "Production cost" column of "Grey v-neck shirt" in table "inventory-lines-table" should be "$200.00"
    And the "Production cost" column of "Grey v-neck shirt - Extra items" in table "inventory-lines-table" should be "$100.00"
    And the "Total items" input should have the value "42"
    And the "Production price" input should have the value "$1,586.50"

  @api @wip
  Scenario: Adding an inventory line to a production order and checking that it's not available to other orders.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    And I click "Add new production order"
    And I uncheck "Include in order" in row containing "Customer High Couture" in table "inventory-lines-table"
    And I press "Save"
    ## Clicking the first row on the production orders view. The link title should be changed.
    And I click "Production order"
    When I click "Edit"
    Then the "Include in order" checkbox in row containing "Customer High Couture" in table "inventory-lines-table" should be unchecked

  @api
  Scenario: Test URL generation for create link.
    Given I am logged in as a user with the "authenticated user" role
    And I am on a "season" page titled "Autumn-Winter 2013 Women"
    And I click "Production Orders"
    When I click "Add new production order"
    Then the URL query "field_season" should have the id of "Autumn-Winter 2013 Women"
