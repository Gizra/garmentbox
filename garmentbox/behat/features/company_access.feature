Feature: Test company access
  Verify that user sees and able to edit only content of his own company.

  @api
  Scenario: Group member trying to access another company, should be denied access.
    Given I am logged in as a user from "Imanimo"
     When I go to "/puma"
     Then I should get a "403" HTTP response

  @api
  Scenario: Group member visiting season page outside of contenxt.
    Given I am logged in as a user from "Imanimo"
     When I am on the "Node view" page of the default "item" of "Imanimo"
     Then I should be on "/puma"

  @api
  Scenario: Testing access to item variant.
    Given I am logged in as a user from "Puma"
     When I am on the "Node view" page of the default "item-variant" of "Imanimo"
     Then I should be on "/puma"

  @api
  Scenario Outline: Testing access to production order pages.
    Given I am logged in as a user from "<company>"
     When I am on the "<try-page>" page of the default "production-order" of "Imanimo"
     Then I should be on "<get-page>"
    Examples:
     | company | try-page                 | get-page  |
     | Puma    | Node view                | /puma     |
     | Puma    | Production delivery      | /puma     |
