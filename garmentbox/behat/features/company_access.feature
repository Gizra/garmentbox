Feature: Test company access
  Verify that user sees and is able to edit only content of thier own company.

  @api
  Scenario: Anonymous user trying to access a company, should be denied access.
     Given I go to "/puma"
      Then I should get a "403" HTTP response

  @api
  Scenario: Group member trying to access another company, should be denied access.
    Given I am logged in as a user from "Imanimo"
     When I go to "/puma"
     Then I should get a "403" HTTP response

  @api
  Scenario Outline: Group member should be able to edit group content.
    Given I am logged in as a user from "Imanimo"
     When I am on the "Node view" page of the default "<page>" of "Imanimo"
      And I click "Edit"
     Then I should get a "200" HTTP response

    Examples:
     | page         |
     | item         |
     | item-variant |


