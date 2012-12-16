Feature:
  Add a group member
  I should be able to review all the existing orders

  @api
  Scenario: Correct content is shown on the season orders list.
    Given I am logged in as a user from "Imanimo"
     When I am on the "Season orders" page of the default "season"
     Then the following <row> should appear in the table "orders":
      | order3  | High Couture | N/A | 26 | <date> 5/30/2013 | <date> 5/30/2013 | Shipping |
      And the order "order3" should have these <inventory lines>
      | Variation          | Small | Medium | Large | Total | Status             |
      | Grey v-neck shirt  | 1     | 0      | 20    | 21    | Future production  |
      | Lines v-neck shirt | 0     | 4      | 1     | 5     | Current production |
