Feature: Test company access
  Verify that user sees and able to edit only content of his own company.

  @api
  Scenario Outline: Testing access to season pages.
    Given I am logged in as a user from "<company>"
     When I am on the "<try-page>" page of the default "season" of "Imanimo"
     Then I should be on "<get-page>"
    Examples:
     | company | try-page                 | get-page  |
     | Puma    | Node view                | /puma     |
     | Puma    | Season tasks             | /puma     |
     | Puma    | Season items             | /puma     |
     | Puma    | Season inventory         | /puma     |
     | Puma    | Season orders            | /puma     |
     | Puma    | Season orders            | /puma     |
     | Puma    | Season production orders | /puma     |
     | Puma    | Season line sheet        | /puma     |

  @api
  Scenario: Testing access to item.
    Given I am logged in as a user from "Puma"
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
