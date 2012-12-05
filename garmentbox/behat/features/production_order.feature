Feature: Test production order flow
  Test the addition and edit forms of production order nodes.

  @javascript
  Scenario: Viewing the add production-order page, with different Quantity/ Size.
    Given I am logged in as "user"
      And I am on the "Add a production order" page of the default "season"
     Then the table "inventory" should have the following <contents>:
      | Include in order   | Item variation                   | Small   | Medium  | Large   | Fabric  | Production cost |
      | <checkbox> checked | Grey v-neck shirt                | 1       | 2       | 20      | <image> | $1,150.00       |
      | <checkbox>         | Grey v-neck shirt - Extra items  | <input> | <input> | <input> |         | $0.00           |
      | <checkbox> checked | Lines v-neck shirt               |         | 8       | 7       | <image> | $397.50         |

  @javascript
  Scenario: Testing price re-calculation.
    Given I am logged in as "user"
      And I am on the "Add a production order" page of the default "season"
      And I click "Grey v-neck shirt"
      And I uncheck "Include in order" in row containing "Customer: High Couture" in table "inventory"
     When I click "Include in order" in row containing "Grey v-neck shirt - Extra items" in table "inventory"
      And I fill in "Small" with "2" in row containing "Grey v-neck shirt - Extra items" in table "inventory"
     Then the "Production cost" column of "Grey v-neck shirt" in table "inventory" should be "$200.00"
      And the "Production cost" column of "Grey v-neck shirt - Extra items" in table "inventory" should be "$100.00"
      And the "Total items" input should have the value "42"
      And the "Production price" input should have the value "$1,586.50"

  @api
  Scenario: Adding an inventory line to a production order and checking that it's not available to other orders.
    Given I am logged in as a user with the "authenticated user" role
      And I am on the "Add a production order" page of the default "season"
      And I uncheck "Include in order" in row containing "Customer: High Couture" in table "inventory"
      And I fill in "Title" with "Test production order"
      And I press "Save"
     When I click "Edit"
     Then the "Include in order" checkbox in row containing "Customer: High Couture" in table "inventory" should be unchecked

  @javascript
  Scenario: Viewing the add production-order page with detailed variant information.
    Given I am logged in as "user"
      And I am on the "Add a production order" page of the default "season"
      And I click "Grey v-neck shirt"
     When I check "Include in order" in row containing "Grey v-neck shirt - Extra items" in table "inventory"
     Then the table "inventory" should have the following <contents>:
      | Include in order    | Item variation                  | Small   | Medium  | Large   | Fabric  | Production cost |
      | <checkbox> checked  | Grey v-neck shirt               | 1       | 2       | 20      | <image> | $1,150.00       |
      | <checkbox> checked  | Customer: High Couture          | 1       |         | 20      |         | $1,050.00       |
      | <checkbox> checked  | Customer: Main                  |         | 2       |         |         | $100.00         |
      | <checkbox>          | Grey v-neck shirt - Extra items | <input> | <input> | <input> |         | $0.00           |

  @api
  Scenario: Creating an extra inventory line on the production order form.
    Given I am logged in as a user with the "authenticated user" role
      And I am on the "Add a production order" page of the default "season"
     When I check "Include in order" in row containing "Lines v-neck shirt - Extra items" in table "inventory"
      And I fill in "Medium" with "212" in row containing "Lines v-neck shirt - Extra items" in table "inventory"
      And I fill in "Title" with "Test production order"
      And I press "Save"
      And I click "Edit"
     Then the following <row> should appear in the table "inventory" :
      | <checkbox> checked  | Customer: Main | | 212 | | | $5,618.00 |

  @api
  Scenario: Test URL generation for create link.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the "Add a production order" page of the default "season"
     Then the URL query "field_season" should have the id of "Autumn-Winter 2013 Women"

