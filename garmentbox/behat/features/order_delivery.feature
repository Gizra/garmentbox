Feature: Production order delivery.
  Test the production order delivery flow.

  @javascript
  Scenario: Creating a production order and viewing the delivery tab.
    Given I am logged in as "user"
      And I am on the "Add a production order" page of the default "season"
      And I press "Save"
     When I click "Production delivery"
     Then the table "inventory" should have the following <contents>:
      | Received   | Item variation             | Type      | Small         | Medium        | Large          | Production price |
      | <checkbox> | Lines v-neck shirt         | Received  |               | <textfield> 8 | <textfield> 7  | $397.50          |
      | <checkbox> | Grey v-neck shirt Received | Received  | <textfield> 2 | <textfield> 2 | <textfield> 20 | $1,150.00        |
      | <checkbox> | Salmon Vest dress Received | Received  | <textfield>   | <textfield>   | <textfield> 23 | $989.00          |

  @api
  Scenario: Setting a production order as delivered and viewing the delivery tab.
    Given I am logged in as a user with the "authenticated user" role
      And I am on a "Production delivery" page of the default "season"




