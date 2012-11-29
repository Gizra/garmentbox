Feature: Production order delivery.
  Allow user to mark the items that were received from production.

#  @javascript
#  Scenario: Creating a production order and viewing the delivery tab.
#    Given I am logged in as "user"
#      And I am on the "Add a production order" page of the default "season"
#      And I press "Save"
#     When I click "Production delivery"
#     Then the table "inventory" should have the following <contents>:
#      | Received   | Item variation             | Type      | Small         | Medium        | Large          | Production price |
#      | <checkbox> | Lines v-neck shirt         | Received  |               | <textfield> 8 | <textfield> 7  | $397.50          |
#      | <checkbox> | Grey v-neck shirt Received | Received  | <textfield> 2 | <textfield> 2 | <textfield> 20 | $1,150.00        |
#      | <checkbox> | Salmon Vest dress Received | Received  | <textfield>   | <textfield>   | <textfield> 23 | $989.00          |

#  @api @wip
#  Scenario: Setting a production order as delivered and viewing the delivery tab.
#    Given I am logged in as a user with the "authenticated user" role
#      And I am on a "Production delivery" page of the default "season"
#     When I check "Received" in row containing "Lines v-neck shirt" in table "delivery-inventory"
#      And I fill in "Medium" with "7" in row containing "Received" in table "delivery-inventory"
#      And I fill in "Large" with "9" in row containing "Received" in table "delivery-inventory"
#      And I fill in "Medium" with "0" in row containing "Customer: Gap" in table "delivery-inventory"
#      And I fill in "Large" with "3" in row containing "Defective" in table "delivery-inventory"
#     Then the table "delivery-inventory" should have the following <contents>:
#      | Received           | Item variation             | Type      | Small         | Medium        | Large          | Production price |
#      | <checkbox> checked | Lines v-neck shirt         | Received  |               | <textfield> 7 | <textfield> 9  | <ignore>         |
#      |                    |                            | Original  |               | 8             | 7              | <ignore>         |
#      |                    |                            | Missing   |               | 8             | 7              | <ignore>         |
#      |                    |                            | Defective |               | 8             | 7              | <ignore>         |
#      |                    |                            | Extras    |               | 8             | 7              | <ignore>         |
#      |                    | Grey v-neck shirt Received | Received  | <textfield> 2 | <textfield> 2 | <textfield> 20 | $1,150.00        |
#      |                    | Salmon Vest dress Received | Received  | <textfield>   | <textfield>   | <textfield> 23 | $989.00          |
