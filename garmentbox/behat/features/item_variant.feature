Feature: Test item variant page
  Verify the BOM and BOL tables are shown correctly and that the prices are
  presented correctly.

  @api
  Scenario: Verify that the basic information is shown correctly.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the default "item-variant" page
     Then I should see the heading "Pink Vest dress"
      And the "production" price should be "$28.75"
      And the "wholesale" price should be "$30.00"
      And the "retail" price should be "$34.00"

  @api
  Scenario: Test the tabs of an item variant.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the default "item-variant" page
     Then I should see the following <links>
      | links             |
      | Main              |
      | Pink Vest dress   |
      | Salmon Vest dress |
      | Peach Vest dress  |

  @api
  Scenario: Test the prices on the BOM table.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the default "item-variant" page
     Then I should see a table titled "Bill of materials" with the following <contents>:
      | Quantity | Material and vendor                          | Unit  | Price | Operations  |
      | 2.50     | Tan/Brown 2-Hole Shell [Fashion 'n' Fabrics] | Meter | $8.75 | Edit Delete |
      And the BOM total should be "$8.75"

  @api
  Scenario: Test the prices on the BOL table.
    Given I am logged in as a user with the "authenticated user" role
     When I am on the default "item-variant" page
     Then I should see a table titled "Bill of labour" with the following <contents>:
      | Price   | Labour term | Operations  |
      | $10.00  | Cutting     | Edit Delete |
      | $10.00  | Sewing      | Edit Delete |
