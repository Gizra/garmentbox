Feature: Test company access
  Verify that user sees and able to edit only content of his own company.

  @api @wip
  Scenario: Testing wrong access to season items page.
    Given I am logged in as a user from "Puma"
     When I am on the "Season items" page of the default "season" of "Imanimo"
     Then I should be on 'puma'

