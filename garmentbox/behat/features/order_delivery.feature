Feature: Production order delivery.
  Test the production order delivery flow.

  @javascript
  Scenario: Creating a production order and clicking around the delivery form.
    Given I am logged in as "user"
      And I am on the "Add a production order" page of the default "season"
      And I press "Save"
      And I click "Production delivery"
     Then the table "inventory" should have the following <contents>:
      | Received | Item variation                   | Small   | Medium  | Large   |  Production cost |
      ##