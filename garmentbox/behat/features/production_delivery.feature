Feature: Production order delivery.
  Allow user to mark the items that were received from production.

  @javascript
  Scenario: Viewing the delivery tab.
    Given I am logged in as "user"
     When I am on a "Production delivery" page of the default "production-order"
     Then the table "delivery-inventory" should have the following <contents>:
      | Received   | Item variation             | Type      | Small          | Medium         | Large          | Production price |
      | <checkbox> | Black v-neck shirt         | Received  | <textfield> 21 | <textfield> 6  |                | $1,215.00          |

  @javascript
  Scenario: Setting a production order as delivered and viewing the delivery tab.
    Given I am logged in as "user"
      And I am on a "Production delivery" page of the default "production-order"
     When I click "Received" in row containing "Black v-neck shirt" in table "delivery-inventory"
      And I fill in "Small" with "16" in row containing "Received" in table "delivery-inventory"
      And I fill in "Medium" with "9" in row containing "Received" in table "delivery-inventory"
      And I fill in "Small" with "3" in row containing "Customer: Gap" in table "delivery-inventory"
      And I fill in "Small" with "13" in row containing "Customer: N/A" in table "delivery-inventory"
      And I fill in "Medium" with "3" in row containing "Defective" in table "delivery-inventory"
      And I press "Save"
     Then the table "delivery-inventory" should have the following <contents>:
      | Received           | Item variation             | Type      | Small          | Medium        | Large | Production price |
      | <checkbox> checked | Black v-neck shirt         | Received  | <textfield> 16 | <textfield> 9 |       | $1,125.00        |
      |                    |                            | Original  | 21             | 6             |       | $1,215.00        |
      |                    |                            | Missing   | 2              |               |       | $90.00           |
      |                    |                            | Missing   | 3              |               |       | $135.00          |
      |                    |                            | Defective | <textfield>    | <textfield> 3 |       | $135.00          |
      |                    |                            | Extras    |                | 3             |       | $135.00          |
